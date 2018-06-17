#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../env/type_impl.h"
#include "../../env/operator_overload.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"
#include <assert.h>

il_factor* il_factor_wrap_explicit_binary_op(il_factor_explicit_binary_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_explicit_binary_op;
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

void il_factor_explicit_binary_op_dump(il_factor_explicit_binary_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	il_factor_dump(self->arg, depth + 1);
}

void il_factor_explicit_binary_op_generate(il_factor_explicit_binary_op* self, enviroment* env) {
	il_factor_generate(self->arg, env);
	il_factor_generate(self->receiver, env);
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, self->index);
}

void il_factor_explicit_binary_op_load(il_factor_explicit_binary_op* self, enviroment* env) {
	il_factor_load(self->receiver, env);
	il_factor_load(self->arg, env);
	self->index = il_factor_binary_op_index2(self->receiver, self->arg, self->type, env);
	assert(self->index != -1);
}

generic_type* il_factor_explicit_binary_op_eval(il_factor_explicit_binary_op* self, enviroment* env) {
	generic_type* gt = il_factor_eval(self->receiver, env);
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(gt)), self->index);
	return operator_ov->return_gtype;
}

void il_factor_explicit_binary_op_delete(il_factor_explicit_binary_op* self) {
	il_factor_delete(self->receiver);
	il_factor_delete(self->arg);
	MEM_FREE(self);
}