#include "il_factor_childa_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

ILChildaOp* NewILChildaOp(OperatorType type) {
	ILChildaOp* ret = (ILChildaOp*)MEM_MALLOC(sizeof(ILChildaOp));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

GenericType* EvalILChildaOp(ILChildaOp * self, Enviroment * env, CallContext* cctx) {
	GenericType* gtype = EvalILFactor(self->parent->Arg, env, cctx);
	if(self->operator_index == -1) {
		//GenerateILFactor(self->parent->Arg, env);
		if(GENERIC2TYPE(gtype) == TYPE_INT) {
			return TYPE2GENERIC(TYPE_INT);
		} else if(GENERIC2TYPE(gtype) == TYPE_BOOL) {
			return TYPE2GENERIC(TYPE_BOOL);
		} else {
			assert(false);
		}
	} else {
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		assert(self->operator_index != -1);
		OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gtype)), self->operator_index);
		return ApplyILUnaryOp(self->parent, operator_ov->ReturnGType, env, cctx);
	}
}

void GenerateILChildaOp(ILChildaOp* self, Enviroment* env, CallContext* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->Arg, env, cctx);
		GenericType* gtype = EvalILFactor(self->parent->Arg, env, cctx);
		if(GENERIC2TYPE(gtype) == TYPE_INT) {
			AddOpcodeBuf(env->Bytecode, OP_IFLIP);
		} else if(GENERIC2TYPE(gtype) == TYPE_BOOL) {
			AddOpcodeBuf(env->Bytecode, OP_BFLIP);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->Arg, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILChildaOp(ILChildaOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gtype = EvalILFactor(self->parent->Arg, env, cctx);
	if(GENERIC2TYPE(gtype) != TYPE_INT &&
	   GENERIC2TYPE(gtype) != TYPE_BOOL) {
		self->operator_index = GetIndexILUnaryOp(self->parent, env, cctx);
	}
}

void DeleteILChildaOp(ILChildaOp* self) {
	MEM_FREE(self);
}

char* ILChildaOpToString(ILChildaOp* self, Enviroment* env) {
	return ILUnaryOpToString_simple(self->parent, env);
}