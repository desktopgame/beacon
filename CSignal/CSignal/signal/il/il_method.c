#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "il_parameter.h"

//proto
static void il_method_parameter_delete(vector_item item);

il_method * il_method_new(const char * name) {
	il_method* ret = (il_method*)malloc(sizeof(il_method));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->return_type = NULL;
	ret->statement_list = il_stmt_list_new();
	return ret;
}

void il_method_dump(il_method * self, int depth) {
	text_putindent(depth);
	printf("method %s -> %s", self->name, self->return_type->name);
	text_putline();
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		il_parameter* p = (il_parameter*)e;
		il_parameter_dump(p, depth + 1);
	}
	il_stmt_list_dump(self->statement_list, depth + 1);
}

void il_method_delete(il_method * self) {
	if (self == NULL) {
		return;
	}
	free(self->name);
	vector_delete(self->parameter_list, il_method_parameter_delete);
	il_type_delete(self->return_type);
	il_stmt_list_delete(self->statement_list);
	free(self);
}

//private
static void il_method_parameter_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}