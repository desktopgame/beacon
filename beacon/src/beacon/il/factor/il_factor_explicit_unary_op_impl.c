#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include "../../env/operator_overload.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"

il_factor* il_factor_wrap_explicit_unary_op(il_factor_explicit_unary_op* self) {
	il_factor* ret = il_factor_new(ilfactor_explicit_unary_op);
	ret->u.exp_unary_op = self;
	return ret;
}

il_factor_explicit_unary_op* il_factor_explicit_unary_op_new(operator_type type) {
	il_factor_explicit_unary_op* ret = (il_factor_explicit_unary_op*)MEM_MALLOC(sizeof(il_factor_explicit_unary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->index = -1;
	return ret;
}

void il_factor_explicit_unary_op_dump(il_factor_explicit_unary_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(stdout, self->type);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
}

void il_factor_explicit_unary_op_generate(il_factor_explicit_unary_op* self, enviroment* env, call_context* cctx) {
	il_factor_generate(self->receiver, env, cctx);
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, self->index);
}

void il_factor_explicit_unary_op_load(il_factor_explicit_unary_op* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->receiver, env, cctx);
	self->index = il_factor_unary_op_index2(self->receiver, self->type, env, cctx);
	assert(self->index != -1);
}

generic_type* il_factor_explicit_unary_op_eval(il_factor_explicit_unary_op* self, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(self->receiver, env, cctx);
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->return_gtype;
}

void il_factor_explicit_unary_op_delete(il_factor_explicit_unary_op* self) {
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}