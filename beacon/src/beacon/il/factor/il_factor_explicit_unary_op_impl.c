#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"

il_factor* WrapILExplicitUnaryOp(il_factor_explicit_unary_op* self) {
	il_factor* ret = il_factor_new(ILFACTOR_EXPLICIT_UNARY_OP_T);
	ret->u.exp_unary_op = self;
	return ret;
}

il_factor_explicit_unary_op* NewILExplicitUnaryOp(OperatorType type) {
	il_factor_explicit_unary_op* ret = (il_factor_explicit_unary_op*)MEM_MALLOC(sizeof(il_factor_explicit_unary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->index = -1;
	return ret;
}

void GenerateILExplicitUnaryOp(il_factor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}

void LoadILExplicitUnaryOp(il_factor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->receiver, env, cctx);
	self->index = GetIndexILUnaryOp2(self->receiver, self->type, env, cctx);
	assert(self->index != -1);
}

generic_type* EvalILExplicitUnaryOp(il_factor_explicit_unary_op* self, Enviroment* env, CallContext* cctx) {
	generic_type* gt = EvalILFactor(self->receiver, env, cctx);
	operator_overload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->return_gtype;
}

void DeleteILExplicitUnaryOp(il_factor_explicit_unary_op* self) {
	DeleteILFactor(self->receiver);
	MEM_FREE(self);
}