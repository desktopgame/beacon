#include "il_factor_string_impl.h"
#include <stdlib.h>
#include<stdio.h>
#include "../../util/text.h"

il_factor * il_factor_wrap_string(il_factor_string * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = factor_squote;
	ret->u.string_ = self;
	return ret;
}

il_factor_string * il_factor_string_new(const char * name) {
	il_factor_string* ret = (il_factor_string*)malloc(sizeof(il_factor_string));
	ret->value = text_strdup(name);
	return ret;
}

void il_factor_string_dump(il_factor_string * self, int depth) {
	text_putindent(depth);
	printf("String %s", self->value);
	text_putline();
}

void il_factor_string_delete(il_factor_string * self) {
	free(self->value);
	free(self);
}
