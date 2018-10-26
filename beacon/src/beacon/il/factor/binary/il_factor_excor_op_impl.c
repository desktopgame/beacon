#include "il_factor_excor_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"

il_factor_excor_op* NewILExcorOp(OperatorType type) {
	il_factor_excor_op* ret = (il_factor_excor_op*)MEM_MALLOC(sizeof(il_factor_excor_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILExcorOp(il_factor_excor_op * self, Enviroment* env, CallContext* cctx) {
	generic_type* lgtype = EvalILFactor(self->parent->left, env, cctx);
	generic_type* rgtype = EvalILFactor(self->parent->right, env, cctx);
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
	return ApplyILBinaryOp(self->parent, operator_ov->return_gtype, env, cctx);
}

void GenerateILExcorOp(il_factor_excor_op* self, Enviroment* env, CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, OP_IEXCOR);
		} else if(IsBoolBoolBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, OP_BEXCOR);
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

void LoadILExcorOp(il_factor_excor_op* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx) &&
	   !IsBoolBoolBinaryOp(self->parent, env, cctx)) {
	self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILExcorOp(il_factor_excor_op* self) {
	MEM_FREE(self);
}

char* ILExcorOpToString(il_factor_excor_op* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}