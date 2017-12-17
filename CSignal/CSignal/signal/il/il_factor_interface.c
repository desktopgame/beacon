#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "../util/text.h"
#include <stdio.h>

void il_factor_dump(il_factor * self, int depth) {
	if (self == NULL) {
		text_putindent(depth);
		printf("c-null");
		text_putline();
		return;
	}
	switch (self->type) {
		case factor_int:
			il_factor_int_dump(self->u.int_, depth);
			break;
		case factor_double:
			il_factor_double_dump(self->u.double_, depth);
			break;
		case factor_cquote:
			il_factor_char_dump(self->u.char_, depth);
			break;
		case factor_squote:
			il_factor_string_dump(self->u.string_, depth);
			break;
		case factor_call:
			il_factor_call_dump(self->u.call_, depth);
			break;
		case factor_invoke:
			il_factor_invoke_dump(self->u.invoke_, depth);
			break;
		case factor_variable:
			il_factor_variable_dump(self->u.variable_, depth);
			break;
		default:
			fprintf(stderr, "指定の種類のファクターの出力には未対応です\n");
			break;
	}
}

void il_factor_delete(il_factor * self) {
	if (self == NULL) {
		return;
	}
	switch (self->type) {
		case factor_int:
			il_factor_int_delete(self->u.int_);
			break;
		case factor_double:
			il_factor_double_delete(self->u.double_);
			break;
		case factor_cquote:
			il_factor_char_delete(self->u.char_);
			break;
		case factor_squote:
			il_factor_string_delete(self->u.string_);
			break;
		case factor_call:
			il_factor_call_delete(self->u.call_);
			break;
		case factor_invoke:
			il_factor_invoke_delete(self->u.invoke_);
			break;
		case factor_variable:
			il_factor_variable_delete(self->u.variable_);
			break;
		default:
			fprintf(stderr, "指定の種類のファクターの開放には未対応です\n");
			break;
	}
	free(self);
}
