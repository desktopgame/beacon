#include "il_factor_call_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"

il_factor * il_factor_wrap_call(il_factor_call * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = factor_call;
	ret->u.call_ = self;
	return ret;
}

il_factor_call * il_factor_call_new(const char * name) {
	il_factor_call* ret = (il_factor_call*)malloc(sizeof(il_factor_call));
	ret->name = text_strdup(name);
	ret->argument_list = il_argument_list_new();
	return ret;
}

void il_factor_call_dump(il_factor_call * self, int depth) {
	text_putindent(depth);
	printf("call %s", self->name);
	text_putline();
	il_argument_list_dump(self->argument_list, depth + 1);
}

void il_factor_call_delete(il_factor_call * self) {
	il_argument_list_delete(self->argument_list);
	free(self->name);
	free(self);
}
