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
		default:
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
		default:
			break;
	}
	free(self);
}
