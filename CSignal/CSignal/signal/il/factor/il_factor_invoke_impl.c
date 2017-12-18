#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../util/text.h"

il_factor * il_factor_wrap_invoke(il_factor_invoke * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_invoke;
	ret->u.invoke_ = self;
	return ret;
}

il_factor_invoke * il_factor_invoke_new(const char * name) {
	il_factor_invoke* ret = (il_factor_invoke*)malloc(sizeof(il_factor_invoke));
	ret->name = text_strdup(name);
	ret->argument_list = il_argument_list_new();
	ret->receiver = NULL;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke * self, int depth) {
	text_putindent(depth);
	printf("invoke %s", self->name);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	il_argument_list_dump(self->argument_list, depth + 1);
}

void il_factor_invoke_delete(il_factor_invoke * self) {
	il_argument_list_delete(self->argument_list);
	free(self->name);
	il_factor_delete(self->receiver);
	free(self);
}
