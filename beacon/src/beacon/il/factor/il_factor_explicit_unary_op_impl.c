#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"

ILFactor* WrapILExplicitUnaryOp(ILFactor_explicit_unary_op* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_EXPLICIT_UNARY_OP_T);
	ret->u.exp_unary_op = self;
	return ret;
}

ILFactor_explicit_unary_op* NewILExplicitUnaryOp(OperatorType type) {
	ILFactor_explicit_unary_op* ret = (ILFactor_explicit_unary_op*)MEM_MALLOC(sizeof(ILFactor_explicit_unary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->index = -1;
	return ret;
}

void GenerateILExplicitUnaryOp(ILFactor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}

void LoadILExplicitUnaryOp(ILFactor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->receiver, env, cctx);
	self->index = GetIndexILUnaryOp2(self->receiver, self->type, env, cctx);
	assert(self->index != -1);
}

GenericType* EvalILExplicitUnaryOp(ILFactor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->receiver, env, cctx);
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitUnaryOp(ILFactor_explicit_unary_op* self) {
	DeleteILFactor(self->receiver);
	MEM_FREE(self);
}