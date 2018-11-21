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

static bc_Opcode operator_to_iopcode(bc_OperatorType type);
static bc_Opcode operator_to_dopcode(bc_OperatorType type);
static bc_Opcode operator_to_copcode(bc_OperatorType type);

ILCompareOp* NewILCompareOp(bc_OperatorType type) {
	ILCompareOp* ret = (ILCompareOp*)MEM_MALLOC(sizeof(ILCompareOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILCompareOp(ILCompareOp * self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* ret = bc_TYPE2GENERIC(BC_TYPE_BOOL);
	assert(ret != NULL);
	return ret;
}

void GenerateILCompareOp(ILCompareOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_iopcode(self->Type));
		} else if(IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_dopcode(self->Type));
		} else if(IsCharCharBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_copcode(self->Type));
		} else {
			bc_Panic(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
				bc_OperatorToString(self->Type)
			);
//			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILCompareOp(ILCompareOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !IsDoubleDoubleBinaryOp(self->Parent, env, cctx) &&
	   !IsCharCharBinaryOp(self->Parent, env, cctx)) {
	self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILCompareOp(ILCompareOp* self) {
	MEM_FREE(self);
}

char* ILCompareOpToString(ILCompareOp* self, bc_Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}
//static
static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
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

static bc_Opcode operator_to_dopcode(bc_OperatorType type) {
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
static bc_Opcode operator_to_copcode(bc_OperatorType type) {
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