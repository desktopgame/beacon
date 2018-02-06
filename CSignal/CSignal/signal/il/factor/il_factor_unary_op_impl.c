#include "il_factor_unary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"

typedef enum u_operator_t {
	u_not,
	u_neg
} u_operator_t;

static opcode u_operator_to_opi(u_operator_t c);
static opcode u_operator_to_opd(u_operator_t c);
static opcode u_operator_to_opb(u_operator_t c);

il_factor * il_factor_wrap_unary(il_factor_unary_op * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_unary_op;
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * il_factor_unary_op_new(ilunary_op_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)MEM_MALLOC(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	return ret;
}

void il_factor_unary_op_dump(il_factor_unary_op * self, int depth) {
	text_putindent(depth);
	switch (self->type) {
		case ilunary_not:
			text_printf("!");
			break;
		case ilunary_neg:
			text_printf("-");
			break;
		default:
			break;
	}
	text_putline();
	il_factor_dump(self->a, depth + 1);
}

void il_factor_unary_op_generate(il_factor_unary_op * self, enviroment* env) {
	il_factor_generate(self->a, env);
	type* cls = il_factor_eval(self->a, env);
	if (cls == CL_INT) {
		assert(self->type == ilunary_neg);
		opcode_buf_add(env->buf, (vector_item)u_operator_to_opi(u_neg));
	} else if (cls == CL_DOUBLE) {
		assert(self->type == ilunary_neg);
		opcode_buf_add(env->buf, (vector_item)u_operator_to_opd(u_neg));
	} else if (cls == CL_BOOL) {
		assert(self->type == ilunary_not);
		opcode_buf_add(env->buf, (vector_item)u_operator_to_opb(u_not));
	} else {
		assert(false);
	}
}

void il_factor_unary_op_load(il_factor_unary_op * self, enviroment * env, il_ehandler * eh) {
}

type * il_factor_unary_op_eval(il_factor_unary_op * self, enviroment * env) {
	if (self->type == ilunary_neg) {
		return il_factor_eval(self->a, env);
	} else if (self->type == ilunary_not) {
		return CL_BOOL;
	}
	return NULL;
}

void il_factor_unary_op_delete(il_factor_unary_op * self) {
	il_factor_delete(self->a);
	MEM_FREE(self);
}

static opcode u_operator_to_opi(u_operator_t c) {
	assert(c == u_neg);
	return op_ineg;
}

static opcode u_operator_to_opd(u_operator_t c) {
	assert(c == u_neg);
	return op_dneg;
}

static opcode u_operator_to_opb(u_operator_t c) {
	assert(c == u_not);
	return op_bnot;
}