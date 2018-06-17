#include "il_factor_not_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/type_impl.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

il_factor_not_op* il_factor_not_op_new(operator_type type) {
	il_factor_not_op* ret = (il_factor_not_op*)MEM_MALLOC(sizeof(il_factor_not_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

void il_factor_not_op_dump(il_factor_not_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_not_op_eval(il_factor_not_op * self, enviroment * env) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void il_factor_not_op_generate(il_factor_not_op* self, enviroment* env) {
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->a, env);
		if(il_error_panic()) {
			return;
		}
		generic_type* gt = il_factor_eval(self->parent->a, env);
		if(GENERIC2TYPE(gt) == TYPE_BOOL) {
			opcode_buf_add(env->buf, op_bnot);
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->a, env);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_not_op_load(il_factor_not_op* self, enviroment* env) {
	generic_type* gt = il_factor_eval(self->parent->a, env);
	if(GENERIC2TYPE(gt) != TYPE_BOOL) {
		self->operator_index = il_factor_unary_op_index(self->parent, env);
	}
}

void il_factor_not_op_delete(il_factor_not_op* self) {
	MEM_FREE(self);
}

char* il_factor_not_op_tostr(il_factor_not_op* self, enviroment* env) {
	return il_factor_unary_op_tostr_simple(self->parent, env);
}