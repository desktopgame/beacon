#include "il_factor_unary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"

il_factor * il_factor_wrap_unary(il_factor_unary_op * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_unary_op;
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * il_factor_unary_op_new(ilunary_op_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)malloc(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	return ret;
}

void il_factor_unary_op_dump(il_factor_unary_op * self, int depth) {
	text_putindent(depth);
	switch (self->type) {
		case ilunary_not:
			printf("!");
			break;
		case ilunary_neg:
			printf("-");
			break;
		default:
			break;
	}
	text_putline();
	il_factor_dump(self->a, depth + 1);
}

void il_factor_unary_op_delete(il_factor_unary_op * self) {
	il_factor_delete(self->a);
	free(self);
}
