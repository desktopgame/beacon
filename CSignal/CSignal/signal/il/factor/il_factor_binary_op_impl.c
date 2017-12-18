#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"

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

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	free(self);
}
