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
	ret->Kind.ExpUnaryOp = self;
	return ret;
}

ILExplicitUnaryOp* NewILExplicitUnaryOp(OperatorType type) {
	ILExplicitUnaryOp* ret = (ILExplicitUnaryOp*)MEM_MALLOC(sizeof(ILExplicitUnaryOp));
	ret->Type = type;
	ret->Receiver = NULL;
	ret->Index = -1;
	return ret;
}

void GenerateILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->Index);
}

void LoadILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Receiver, env, cctx);
	self->Index = GetIndexILUnaryOp2(self->Receiver, self->Type, env, cctx);
	assert(self->Index != -1);
}

GenericType* EvalILExplicitUnaryOp(ILExplicitUnaryOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->Receiver, env, cctx);
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->Index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitUnaryOp(ILExplicitUnaryOp* self) {
	DeleteILFactor(self->Receiver);
	MEM_FREE(self);
}