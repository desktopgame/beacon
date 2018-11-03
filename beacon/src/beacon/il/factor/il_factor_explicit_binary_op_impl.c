#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"
#include <assert.h>

ILFactor* WrapILExplicitBinaryOp(ILExplicitBinaryOp* self) {
	ILFactor* ret = NewILFactor(ILFACTOR_EXPLICIT_BINARY_OP_T);
	ret->Kind.ExpBinaryOp = self;
	return ret;
}

ILExplicitBinaryOp* NewILExplicitBinaryOp(OperatorType type) {
	ILExplicitBinaryOp* ret = (ILExplicitBinaryOp*)MEM_MALLOC(sizeof(ILExplicitBinaryOp));
	ret->Type = type;
	ret->Receiver = NULL;
	ret->Arg = NULL;
	ret->Index = -1;
	return ret;
}

void GenerateILExplicitBinaryOp(ILExplicitBinaryOp* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Arg, env, cctx);
	GenerateILFactor(self->Receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->Index);
}

void LoadILExplicitBinaryOp(ILExplicitBinaryOp* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Receiver, env, cctx);
	LoadILFactor(self->Arg, env, cctx);
	self->Index = GetIndexILBinaryOp2(self->Receiver, self->Arg, self->Type, env, cctx);
	assert(self->Index != -1);
}

GenericType* EvalILExplicitBinaryOp(ILExplicitBinaryOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->Receiver, env, cctx);
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->Index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitBinaryOp(ILExplicitBinaryOp* self) {
	DeleteILFactor(self->Receiver);
	DeleteILFactor(self->Arg);
	MEM_FREE(self);
}