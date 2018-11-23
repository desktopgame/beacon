#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"

bc_ILFactor* bc_WrapILExplicitUnaryOp(bc_ILExplicitUnaryOp* self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_EXPLICIT_UNARY_OP_T);
	ret->Kind.ExpUnaryOp = self;
	return ret;
}

bc_ILExplicitUnaryOp* bc_NewILExplicitUnaryOp(bc_OperatorType type) {
	bc_ILExplicitUnaryOp* ret = (bc_ILExplicitUnaryOp*)MEM_MALLOC(sizeof(bc_ILExplicitUnaryOp));
	ret->Type = type;
	ret->Receiver = NULL;
	ret->Index = -1;
	return ret;
}

void bc_GenerateILExplicitUnaryOp(bc_ILExplicitUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Receiver, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	bc_AddOpcodeBuf(env->Bytecode, self->Index);
}

void bc_LoadILExplicitUnaryOp(bc_ILExplicitUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Receiver, env, cctx);
	self->Index = bc_GetIndexILUnaryOp2(self->Receiver, self->Type, env, cctx);
	assert(self->Index != -1);
}

bc_GenericType* bc_EvalILExplicitUnaryOp(bc_ILExplicitUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gt = bc_EvalILFactor(self->Receiver, env, cctx);
	bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(gt)), self->Index);
	return operator_ov->ReturnGType;
}

void bc_DeleteILExplicitUnaryOp(bc_ILExplicitUnaryOp* self) {
	bc_DeleteILFactor(self->Receiver);
	MEM_FREE(self);
}