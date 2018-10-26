#include "il_factor_compare_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/type_interface.h"

static Opcode operator_to_iopcode(OperatorType type);
static Opcode operator_to_dopcode(OperatorType type);
static Opcode operator_to_copcode(OperatorType type);

il_factor_compare_op* NewILCompareOp(OperatorType type) {
	il_factor_compare_op* ret = (il_factor_compare_op*)MEM_MALLOC(sizeof(il_factor_compare_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

GenericType* EvalILCompareOp(il_factor_compare_op * self, Enviroment* env, CallContext* cctx) {
	GenericType* ret = TYPE2GENERIC(TYPE_BOOL);
	assert(ret != NULL);
	return ret;
}

void GenerateILCompareOp(il_factor_compare_op* self, Enviroment* env, CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->type));
		} else if(IsDoubleDoubleBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_dopcode(self->type));
		} else if(IsCharCharBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_copcode(self->type));
		} else {
			ThrowBCError(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
				OperatorToString(self->type)
			);
//			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILCompareOp(il_factor_compare_op* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx) &&
	   !IsDoubleDoubleBinaryOp(self->parent, env, cctx) &&
	   !IsCharCharBinaryOp(self->parent, env, cctx)) {
	self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILCompareOp(il_factor_compare_op* self) {
	MEM_FREE(self);
}

char* ILCompareOpToString(il_factor_compare_op* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}
//static
static Opcode operator_to_iopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_IGT;
		case OPERATOR_GE_T: return OP_IGE;
		case OPERATOR_LT_T: return OP_ILT;
		case OPERATOR_LE_T: return OP_ILE;
		case OPERATOR_EQ_T: return OP_IEQ;
		case OPERATOR_NOT_EQ_T: return OP_INOTEQ;
	}
	assert(false);
}

static Opcode operator_to_dopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_DGT;
		case OPERATOR_GE_T: return OP_DGE;
		case OPERATOR_LT_T: return OP_DLT;
		case OPERATOR_LE_T: return OP_DLE;
		case OPERATOR_EQ_T: return OP_DEQ;
		case OPERATOR_NOT_EQ_T: return OP_DNOTEQ;
	}
	assert(false);
}
static Opcode operator_to_copcode(OperatorType type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_CGT;
		case OPERATOR_GE_T: return OP_CGE;
		case OPERATOR_LT_T: return OP_CLT;
		case OPERATOR_LE_T: return OP_CLE;
		case OPERATOR_EQ_T: return OP_CEQ;
		case OPERATOR_NOT_EQ_T: return OP_CNOTEQ;
	}
	assert(false);
}