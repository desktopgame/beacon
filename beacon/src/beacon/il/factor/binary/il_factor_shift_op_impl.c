#include "il_factor_shift_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"

static bc_Opcode operator_to_iopcode(bc_OperatorType type);
static bc_Opcode operator_to_dopcode(bc_OperatorType type);

ILShiftOp* NewILShiftOp(bc_OperatorType type) {
	ILShiftOp* ret = (ILShiftOp*)MEM_MALLOC(sizeof(ILShiftOp));
	ret->Parent = NULL;
	ret->Type = type;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILShiftOp(ILShiftOp * self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
	bc_GenericType* rgtype = bc_EvalILFactor(self->Parent->Right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	bc_Type* cint = BC_TYPE_INT;
	bc_Type* cdouble = BC_TYPE_DOUBLE;
	if(bc_GENERIC2TYPE(lgtype) == cint &&
	   bc_GENERIC2TYPE(rgtype) == cint) {
		return bc_TYPE2GENERIC(cint);
	}
	if(bc_GENERIC2TYPE(lgtype) == cint &&
	   bc_GENERIC2TYPE(rgtype) == cint) {
		return bc_TYPE2GENERIC(cdouble);
	}
	if(self->OperatorIndex == -1) {
		bc_Panic(
			BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
			bc_OperatorToString(self->Type)
		);
		return NULL;
	}
	bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
	return ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILShiftOp(ILShiftOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_iopcode(self->Type));
		} else {
			bc_Panic(
				BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
				bc_OperatorToString(self->Type)
			);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILShiftOp(ILShiftOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx)) {
		self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILShiftOp(ILShiftOp* self) {
	MEM_FREE(self);
}

char* ILShiftOpToString(ILShiftOp* self, bc_Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}
//static
static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
	switch(type) {
		case OPERATOR_LSHIFT_T: return OP_ILSH;
		case OPERATOR_RSHIFT_T: return OP_IRSH;
	}
	assert(false);
}

static bc_Opcode operator_to_dopcode(bc_OperatorType type) {
	assert(false);
}