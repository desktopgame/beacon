#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"

il_factor * il_factor_wrap_binary(il_factor_binary_op * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_binary_op;
	ret->u.binary_ = self;
	return ret;
}

il_factor_binary_op * il_factor_binary_op_new(ilbinary_op_type type) {
	il_factor_binary_op* ret = (il_factor_binary_op*)malloc(sizeof(il_factor_binary_op));
	ret->type = type;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void il_factor_binary_op_dump(il_factor_binary_op * self, int depth) {
	text_putindent(depth);
	switch (self->type) {
		case ilbinary_add:
			printf("+");
			break;
		case ilbinary_sub:
			printf("-");
			break;
		case ilbinary_mul:
			printf("*");
			break;
		case ilbinary_div:
			printf("/");
			break;
		case ilbinary_mod:
			printf("%");
			break;


		case ilbinary_bit_or:
			printf("|");
			break;
		case ilbinary_logic_or:
			printf("||");
			break;


		case ilbinary_bit_and:
			printf("&");
			break;
		case ilbinary_logic_and:
			printf("&&");
			break;

		case ilbinary_eq:
			printf("==");
			break;
		case ilbinary_noteq:
			printf("!=");
			break;
		case ilbinary_gt:
			printf(">");
			break;
		case ilbinary_ge:
			printf(">=");
			break;
		case ilbinary_lt:
			printf("<");
			break;
		case ilbinary_le:
			printf("<=");
			break;
		default:
			break;
	}
	text_putline();
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env) {
	il_factor_generate(self->left, env);
	il_factor_generate(self->right, env);
	switch (self->type) {
		case ilbinary_add:
			opcode_buf_add(env->buf, op_add);
			break;
		case ilbinary_sub:
			opcode_buf_add(env->buf, op_sub);
			break;
		case ilbinary_mul:
			opcode_buf_add(env->buf, op_mul);
			break;
		case ilbinary_div:
			opcode_buf_add(env->buf, op_div);
			break;
		case ilbinary_mod:
			opcode_buf_add(env->buf, op_mod);
			break;


		case ilbinary_bit_or:
			opcode_buf_add(env->buf, op_bit_or);
			break;
		case ilbinary_logic_or:
			opcode_buf_add(env->buf, op_logic_or);
			break;


		case ilbinary_bit_and:
			opcode_buf_add(env->buf, op_bit_and);
			break;
		case ilbinary_logic_and:
			opcode_buf_add(env->buf, op_logic_and);
			break;

		case ilbinary_eq:
			opcode_buf_add(env->buf, op_eq);
			break;
		case ilbinary_noteq:
			opcode_buf_add(env->buf, op_noteq);
			break;
		case ilbinary_gt:
			opcode_buf_add(env->buf, op_gt);
			break;
		case ilbinary_ge:
			opcode_buf_add(env->buf, op_ge);
			break;
		case ilbinary_lt:
			opcode_buf_add(env->buf, op_lt);
			break;
		case ilbinary_le:
			opcode_buf_add(env->buf, op_le);
			break;
		default:
			break;
	}
}

class_ * il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env) {
	return NULL;
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	free(self);
}
