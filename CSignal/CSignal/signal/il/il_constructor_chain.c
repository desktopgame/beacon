#include "il_constructor_chain.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_argument.h"
#include <stdio.h>

il_constructor_chain * il_constructor_chain_new() {
	il_constructor_chain* ret = (il_constructor_chain*)MEM_MALLOC(sizeof(il_constructor_chain));
	ret->type = chain_type_this;
	ret->argument_list = vector_new();
	ret->c = NULL;
	ret->constructorIndex = -1;
	return ret;
}

void il_constructor_chain_dump(il_constructor_chain * self, int depth) {
	text_putindent(depth);
	printf("constructor chain");
	text_putline();
	text_putindent(depth);
	if (self->type == chain_type_this) {
		printf("this");
	} else if (self->type == chain_type_super) {
		printf("super");
	}
	text_putline();
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_argument_dump(ilarg, depth + 1);
	}
}

void il_constructor_chain_delete(il_constructor_chain * self) {
	MEM_FREE(self);
}
