#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_parameter.h"
#include "il_type_parameter.h"

//proto
static void il_method_parameter_delete(vector_item item);
static void il_method_stmt_delete(vector_item item);
static void il_method_type_parameter_delete(vector_item item);

il_method * il_method_new(string_view namev) {
	il_method* ret = (il_method*)MEM_MALLOC(sizeof(il_method));
	ret->namev = namev;
	ret->parameter_list = vector_new();
	ret->return_fqcn = generic_cache_new();
	ret->access = access_public_T;
	ret->modifier = modifier_none_T;
	ret->statement_list = vector_new();
	ret->type_parameter_list = vector_new();
	ret->no_stmt = false;
	return ret;
}

void il_method_delete(il_method * self) {
	if (self == NULL) {
		return;
	}
	generic_cache_delete(self->return_fqcn);
	vector_delete(self->parameter_list, il_method_parameter_delete);
	vector_delete(self->statement_list, il_method_stmt_delete);
	vector_delete(self->type_parameter_list, il_method_type_parameter_delete);
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

static void il_method_type_parameter_delete(vector_item item) {
	il_type_parameter* e = (il_type_parameter*)item;
	il_type_parameter_delete(e);
}