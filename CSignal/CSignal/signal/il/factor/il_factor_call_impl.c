#include "il_factor_call_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../il_argument.h"
#include "../../util/text.h"
#include "../../vm/opcode_buf.h"

//proto
static void il_factor_call_argument_list_delete(vector_item item);

il_factor * il_factor_wrap_call(il_factor_call * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_call;
	ret->u.call_ = self;
	return ret;
}

il_factor_call * il_factor_call_new(const char * name) {
	il_factor_call* ret = (il_factor_call*)malloc(sizeof(il_factor_call));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	return ret;
}

void il_factor_call_dump(il_factor_call * self, int depth) {
	text_putindent(depth);
	printf("call %s", self->name);
	text_putline();
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_call_generate(il_factor_call * self, opcode_buf * buf) {
}

void il_factor_call_delete(il_factor_call * self) {
	vector_delete(self->argument_list, il_factor_call_argument_list_delete);
	free(self->name);
	free(self);
}

//private
static void il_factor_call_argument_list_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}
