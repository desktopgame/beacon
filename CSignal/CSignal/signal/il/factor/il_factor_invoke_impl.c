#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"

//proto
static void il_factor_invoke_argument_delete(vector_item item);

il_factor * il_factor_wrap_invoke(il_factor_invoke * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_invoke;
	ret->u.invoke_ = self;
	return ret;
}

il_factor_invoke * il_factor_invoke_new(const char * name) {
	il_factor_invoke* ret = (il_factor_invoke*)malloc(sizeof(il_factor_invoke));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	ret->receiver = NULL;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke * self, int depth) {
	text_putindent(depth);
	printf("invoke %s", self->name);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_invoke_generate(il_factor_invoke * self, enviroment* env) {
}

void il_factor_invoke_delete(il_factor_invoke * self) {
	vector_delete(self->argument_list, il_factor_invoke_argument_delete);
	free(self->name);
	il_factor_delete(self->receiver);
	free(self);
}

//private
static void il_factor_invoke_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}