#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include <assert.h>

static bc_Opcode operator_to_iopcode(bc_OperatorType type);
static bc_Opcode operator_to_dopcode(bc_OperatorType type);

ILArithmeticOp* NewILArithmeticOp(bc_OperatorType type) {
	ILArithmeticOp* ret = (ILArithmeticOp*)MEM_MALLOC(sizeof(ILArithmeticOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILArithmeticOp(ILArithmeticOp * self, bc_Enviroment* env, CallContext* cctx) {
	bc_GenericType* lgtype = EvalILFactor(self->Parent->Left, env, cctx);
	bc_GenericType* rgtype = EvalILFactor(self->Parent->Right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	bc_Type* cint = BC_TYPE_INT;
	bc_Type* cdouble = BC_TYPE_DOUBLE;
	if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(cint);
	}
	if(IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(cdouble);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->OperatorIndex == -1) {
		bc_Panic(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
			bc_OperatorToString(self->Type)
		);
		return NULL;
	}
	bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
	return ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILArithmeticOp(ILArithmeticOp* self, bc_Enviroment* env, CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->OperatorIndex == -1) {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->Type));
		} else if(IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_dopcode(self->Type));
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILArithmeticOp(ILArithmeticOp* self, bc_Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
		self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILArithmeticOp(ILArithmeticOp* self) {
	MEM_FREE(self);
}

char* ILArithmeticOpToString(ILArithmeticOp* self, bc_Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}
//static
static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_IADD;
		case OPERATOR_SUB_T: return OP_ISUB;
		case OPERATOR_MUL_T: return OP_IMUL;
		case OPERATOR_DIV_T: return OP_IDIV;
		case OPERATOR_MOD_T: return OP_IMOD;
	}
	assert(false);
}

static bc_Opcode operator_to_dopcode(bc_OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_DADD;
		case OPERATOR_SUB_T: return OP_DSUB;
		case OPERATOR_MUL_T: return OP_DMUL;
		case OPERATOR_DIV_T: return OP_DDIV;
		case OPERATOR_MOD_T: return OP_DMOD;
	}
	assert(false);
}