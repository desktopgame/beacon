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

static Opcode operator_to_iopcode(OperatorType type);
static Opcode operator_to_dopcode(OperatorType type);

il_factor_arithmetic_op* NewILArithmeticOp(OperatorType type) {
	il_factor_arithmetic_op* ret = (il_factor_arithmetic_op*)MEM_MALLOC(sizeof(il_factor_arithmetic_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILArithmeticOp(il_factor_arithmetic_op * self, Enviroment* env, call_context* cctx) {
	generic_type* lgtype = EvalILFactor(self->parent->left, env, cctx);
	generic_type* rgtype = EvalILFactor(self->parent->right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	type* cint = TYPE_INT;
	type* cdouble = TYPE_DOUBLE;
	if(IsIntIntBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(cint);
	}
	if(IsDoubleDoubleBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(cdouble);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->operator_index == -1) {
		ThrowBCError(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
			OperatorToString(self->type)
		);
		return NULL;
	}
	operator_overload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return ApplyILBinaryOp(self->parent, operator_ov->return_gtype, env, cctx);
}

void GenerateILArithmeticOp(il_factor_arithmetic_op* self, Enviroment* env, call_context* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->type));
		} else if(IsDoubleDoubleBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_dopcode(self->type));
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILArithmeticOp(il_factor_arithmetic_op* self, Enviroment* env, call_context* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx) &&
	   !IsDoubleDoubleBinaryOp(self->parent, env, cctx)) {
		self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILArithmeticOp(il_factor_arithmetic_op* self) {
	MEM_FREE(self);
}

char* ILArithmeticOpToString(il_factor_arithmetic_op* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}
//static
static Opcode operator_to_iopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_IADD;
		case OPERATOR_SUB_T: return OP_ISUB;
		case OPERATOR_MUL_T: return OP_IMUL;
		case OPERATOR_DIV_T: return OP_IDIV;
		case OPERATOR_MOD_T: return OP_IMOD;
	}
	assert(false);
}

static Opcode operator_to_dopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_DADD;
		case OPERATOR_SUB_T: return OP_DSUB;
		case OPERATOR_MUL_T: return OP_DMUL;
		case OPERATOR_DIV_T: return OP_DDIV;
		case OPERATOR_MOD_T: return OP_DMOD;
	}
	assert(false);
}