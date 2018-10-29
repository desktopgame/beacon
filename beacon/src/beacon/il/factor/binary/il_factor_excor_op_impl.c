#include "il_factor_excor_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"

ILExcorOp* NewILExcorOp(OperatorType type) {
	ILExcorOp* ret = (ILExcorOp*)MEM_MALLOC(sizeof(ILExcorOp));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

GenericType* EvalILExcorOp(ILExcorOp * self, Enviroment* env, CallContext* cctx) {
	GenericType* lgtype = EvalILFactor(self->parent->Left, env, cctx);
	GenericType* rgtype = EvalILFactor(self->parent->Right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	if(IsIntIntBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_INT);
	}
	if(IsBoolBoolBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_BOOL);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->operator_index == -1) {
		ThrowBCError(BCERROR_UNDEFINED_EXCOR_OPERATOR_T,
			OperatorToString(self->type)
		);
		return NULL;
	}
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return ApplyILBinaryOp(self->parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILExcorOp(ILExcorOp* self, Enviroment* env, CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->Right, env, cctx);
		GenerateILFactor(self->parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, OP_IEXCOR);
		} else if(IsBoolBoolBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, OP_BEXCOR);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->Right, env, cctx);
		GenerateILFactor(self->parent->Left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILExcorOp(ILExcorOp* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx) &&
	   !IsBoolBoolBinaryOp(self->parent, env, cctx)) {
	self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILExcorOp(ILExcorOp* self) {
	MEM_FREE(self);
}

char* ILExcorOpToString(ILExcorOp* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}