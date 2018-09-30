#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"
#include <assert.h>

il_factor* il_factor_wrap_explicit_binary_op(il_factor_explicit_binary_op* self) {
	il_factor* ret = il_factor_new(ILFACTOR_EXPLICIT_BINARY_OP_T);
	ret->u.exp_binary_op = self;
	return ret;
}

il_factor_explicit_binary_op* il_factor_explicit_binary_op_new(operator_type type) {
	il_factor_explicit_binary_op* ret = (il_factor_explicit_binary_op*)MEM_MALLOC(sizeof(il_factor_explicit_binary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->arg = NULL;
	ret->index = -1;
	return ret;
}

void il_factor_explicit_binary_op_generate(il_factor_explicit_binary_op* self, enviroment* env, call_context* cctx) {
	GenerateILFactor(self->arg, env, cctx);
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->buf, self->index);
}

void il_factor_explicit_binary_OP_LOAD(il_factor_explicit_binary_op* self, enviroment* env, call_context* cctx) {
	LoadILFactor(self->receiver, env, cctx);
	LoadILFactor(self->arg, env, cctx);
	self->index = il_factor_binary_op_index2(self->receiver, self->arg, self->type, env, cctx);
	assert(self->index != -1);
}

generic_type* il_factor_explicit_binary_op_eval(il_factor_explicit_binary_op* self, enviroment* env, call_context* cctx) {
	generic_type* gt = EvalILFactor(self->receiver, env, cctx);
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->return_gtype;
}

void il_factor_explicit_binary_op_delete(il_factor_explicit_binary_op* self) {
	DeleteILFactor(self->receiver);
	DeleteILFactor(self->arg);
	MEM_FREE(self);
}