#include "il_function.h"
#include "../env/generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_type_parameter.h"
#include "il_stmt_interface.h"
#include <stdio.h>

//proto
static void il_function_type_parameter_delete(vector_item item);
static void il_function_parameter_delete(vector_item item);
static void il_function_stmt_delete(vector_item item);

il_function * il_function_new(string_view namev) {
	il_function* ret = (il_function*)MEM_MALLOC(sizeof(il_function));
	ret->namev = namev;
	ret->type_parameter_vec = vector_new();
	ret->parameter_list = vector_new();
	ret->statement_list = vector_new();
	ret->return_fqcn = generic_cache_new();
	return ret;
}

void il_function_delete(il_function * self) {
	vector_delete(self->type_parameter_vec, il_function_type_parameter_delete);
	vector_delete(self->parameter_list, il_function_parameter_delete);
	vector_delete(self->statement_list, il_function_stmt_delete);
	generic_cache_delete(self->return_fqcn);
	MEM_FREE(self);
}

//private
static void il_function_type_parameter_delete(vector_item item) {
	il_type_parameter* e = (il_type_parameter*)item;
	il_type_parameter_delete(e);
}

static void il_function_parameter_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_function_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}