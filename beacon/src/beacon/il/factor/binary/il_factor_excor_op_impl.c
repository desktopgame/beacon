#include "il_factor_excor_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"

ILExcorOp* NewILExcorOp(bc_OperatorType type) {
	ILExcorOp* ret = (ILExcorOp*)MEM_MALLOC(sizeof(ILExcorOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILExcorOp(ILExcorOp * self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
	bc_GenericType* rgtype = bc_EvalILFactor(self->Parent->Right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(BC_TYPE_INT);
	}
	if(IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(BC_TYPE_BOOL);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->OperatorIndex == -1) {
		bc_Panic(BCERROR_UNDEFINED_EXCOR_OPERATOR_T,
			bc_OperatorToString(self->Type)
		);
		return NULL;
	}
	bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
	return ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILExcorOp(ILExcorOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, OP_IEXCOR);
		} else if(IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, OP_BEXCOR);
		} else {
			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILExcorOp(ILExcorOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
	self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILExcorOp(ILExcorOp* self) {
	MEM_FREE(self);
}

char* ILExcorOpToString(ILExcorOp* self, bc_Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}