#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"

il_method * il_method_new(const char * name) {
	il_method* ret = (il_method*)malloc(sizeof(il_method));
	ret->name = text_strdup(name);
	ret->parameter_list = il_parameter_list_new();
	ret->return_type = NULL;
	ret->statement_list = il_stmt_list_new();
	return ret;
}

void il_method_dump(il_method * self, int depth) {
	text_putindent(depth);
	printf("method %s -> %s", self->name, self->return_type->name);
	text_putline();
	il_parameter_list_dump(self->parameter_list, depth + 1);
	il_stmt_list_dump(self->statement_list, depth + 1);
}

void il_method_delete(il_method * self) {
	if (self == NULL) {
		return;
	}
	free(self->name);
	il_parameter_list_delete(self->parameter_list);
	il_type_delete(self->return_type);
	il_stmt_list_delete(self->statement_list);
	free(self);
}
