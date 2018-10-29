#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"

ILFactor* WrapILExplicitUnaryOp(ILExplicitUnaryOp* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_EXPLICIT_UNARY_OP_T);
	ret->u.exp_unary_op = self;
	return ret;
}

ILExplicitUnaryOp* NewILExplicitUnaryOp(OperatorType type) {
	ILExplicitUnaryOp* ret = (ILExplicitUnaryOp*)MEM_MALLOC(sizeof(ILExplicitUnaryOp));
	ret->type = type;
	ret->receiver = NULL;
	ret->index = -1;
	return ret;
}

void GenerateILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}

void LoadILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->receiver, env, cctx);
	self->index = GetIndexILUnaryOp2(self->receiver, self->type, env, cctx);
	assert(self->index != -1);
}

GenericType* EvalILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->receiver, env, cctx);
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitUnaryOp(ILExplicitUnaryOp* self) {
	DeleteILFactor(self->receiver);
	MEM_FREE(self);
}