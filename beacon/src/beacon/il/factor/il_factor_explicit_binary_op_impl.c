#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"
#include <assert.h>

ILFactor* WrapILExplicitBinaryOp(ILFactor_explicit_binary_op* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_EXPLICIT_BINARY_OP_T);
	ret->u.exp_binary_op = self;
	return ret;
}

ILFactor_explicit_binary_op* NewILExplicitBinaryOp(OperatorType type) {
	ILFactor_explicit_binary_op* ret = (ILFactor_explicit_binary_op*)MEM_MALLOC(sizeof(ILFactor_explicit_binary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->arg = NULL;
	ret->index = -1;
	return ret;
}

void GenerateILExplicitBinaryOp(ILFactor_explicit_binary_op* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->arg, env, cctx);
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}

void LoadILExplicitBinaryOp(ILFactor_explicit_binary_op* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->receiver, env, cctx);
	LoadILFactor(self->arg, env, cctx);
	self->index = GetIndexILBinaryOp2(self->receiver, self->arg, self->type, env, cctx);
	assert(self->index != -1);
}

GenericType* EvalILExplicitBinaryOp(ILFactor_explicit_binary_op* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->receiver, env, cctx);
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitBinaryOp(ILFactor_explicit_binary_op* self) {
	DeleteILFactor(self->receiver);
	DeleteILFactor(self->arg);
	MEM_FREE(self);
}