#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_import.h"
#include "il_namespace.h"
#include "il_function.h"

//proto
static void il_top_level_import_delete(VectorItem item);
static void il_top_level_namespace_delete(VectorItem item);
static void il_top_level_function_delete(VectorItem item);
static void il_top_level_stmt_delete(VectorItem item);

il_top_level* il_top_level_new() {
	il_top_level* ret = (il_top_level*)MEM_MALLOC(sizeof(il_top_level));
	ret->import_list = NewVector();
	ret->namespace_list = NewVector();
	ret->statement_list = NewVector();
	ret->function_list = NewVector();
	return ret;
}

void il_top_level_delete(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->import_list, il_top_level_import_delete);
	DeleteVector(self->namespace_list, il_top_level_namespace_delete);
	DeleteVector(self->statement_list, il_top_level_stmt_delete);
	DeleteVector(self->function_list, il_top_level_function_delete);
	MEM_FREE(self);
}

//private
static void il_top_level_import_delete(VectorItem item) {
	il_import* e = (il_import*)item;
	il_import_delete(e);
}

static void il_top_level_namespace_delete(VectorItem item) {
	il_namespace* e = (il_namespace*)item;
	il_namespace_delete(e);
}

static void il_top_level_function_delete(VectorItem item) {
	il_function* e = (il_function*)item;
	il_function_delete(e);
}

static void il_top_level_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}