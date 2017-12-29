#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_parameter.h"

//proto
static void il_method_parameter_delete(vector_item item);
static void il_method_stmt_delete(vector_item item);

il_method * il_method_new(const char * name) {
	il_method* ret = (il_method*)MEM_MALLOC(sizeof(il_method));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->return_type = NULL;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->statement_list = vector_new();
	return ret;
}

void il_method_dump(il_method * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	printf(" ");
	modifier_print(self->modifier);
	printf(" method %s -> %s", self->name, self->return_type->name);
	text_putline();
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		il_parameter* p = (il_parameter*)e;
		il_parameter_dump(p, depth + 1);
	}
	for (int i = 0; i < self->statement_list->length; i++) {
		vector_item e = vector_at(self->statement_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
}

void il_method_delete(il_method * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self->name);
	vector_delete(self->parameter_list, il_method_parameter_delete);
	il_type_delete(self->return_type);
	vector_delete(self->statement_list, il_method_stmt_delete);
	MEM_FREE(self);
}

//private
static void il_method_parameter_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_method_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}