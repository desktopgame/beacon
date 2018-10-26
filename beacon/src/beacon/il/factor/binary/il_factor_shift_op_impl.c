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

static Opcode operator_to_iopcode(OperatorType type);
static Opcode operator_to_dopcode(OperatorType type);

il_factor_shift_op* NewILShiftOp(OperatorType type) {
	il_factor_shift_op* ret = (il_factor_shift_op*)MEM_MALLOC(sizeof(il_factor_shift_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

GenericType* EvalILShiftOp(il_factor_shift_op * self, Enviroment* env, CallContext* cctx) {
	GenericType* lgtype = EvalILFactor(self->parent->left, env, cctx);
	GenericType* rgtype = EvalILFactor(self->parent->right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	type* cint = TYPE_INT;
	type* cdouble = TYPE_DOUBLE;
	if(GENERIC2TYPE(lgtype) == cint &&
	   GENERIC2TYPE(rgtype) == cint) {
		return TYPE2GENERIC(cint);
	}
	if(GENERIC2TYPE(lgtype) == cint &&
	   GENERIC2TYPE(rgtype) == cint) {
		return TYPE2GENERIC(cdouble);
	}
	if(self->operator_index == -1) {
		ThrowBCError(
			BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
			OperatorToString(self->type)
		);
		return NULL;
	}
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return ApplyILBinaryOp(self->parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILShiftOp(il_factor_shift_op* self, Enviroment* env, CallContext* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->type));
		} else {
			ThrowBCError(
				BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
				OperatorToString(self->type)
			);
		}
	} else {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILShiftOp(il_factor_shift_op* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx)) {
		self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILShiftOp(il_factor_shift_op* self) {
	MEM_FREE(self);
}

char* ILShiftOpToString(il_factor_shift_op* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}
//static
static Opcode operator_to_iopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_LSHIFT_T: return OP_ILSH;
		case OPERATOR_RSHIFT_T: return OP_IRSH;
	}
	assert(false);
}

static Opcode operator_to_dopcode(OperatorType type) {
	assert(false);
}