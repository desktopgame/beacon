#include "il_factor_not_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

il_factor_not_op* il_factor_not_op_new(operator_type type) {
	il_factor_not_op* ret = (il_factor_not_op*)MEM_MALLOC(sizeof(il_factor_not_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

generic_type* il_factor_not_op_eval(il_factor_not_op * self, enviroment * env, call_context* cctx) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void il_factor_not_op_generate(il_factor_not_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->a, env, cctx);
		if(bc_error_last()) {
			return;
		}
		generic_type* gt = il_factor_eval(self->parent->a, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_BOOL) {
			opcode_buf_add(env->buf, OP_BNOT);
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->a, env, cctx);
		opcode_buf_add(env->buf, OP_INVOKEOPERATOR);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_not_OP_LOAD(il_factor_not_op* self, enviroment* env, call_context* cctx) {
	 il_factor_load(self->parent->a, env, cctx);
	generic_type* gt = il_factor_eval(self->parent->a, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_BOOL) {
		self->operator_index = il_factor_unary_op_index(self->parent, env, cctx);
	}
}

void il_factor_not_op_delete(il_factor_not_op* self) {
	MEM_FREE(self);
}

char* il_factor_not_op_tostr(il_factor_not_op* self, enviroment* env) {
	return il_factor_unary_op_tostr_simple(self->parent, env);
}