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
static void il_top_level_DeleteNamespace(VectorItem item);
static void il_top_level_function_delete(VectorItem item);
static void il_top_level_stmt_delete(VectorItem item);

il_top_level* NewILToplevel() {
	il_top_level* ret = (il_top_level*)MEM_MALLOC(sizeof(il_top_level));
	ret->import_list = NewVector();
	ret->namespace_list = NewVector();
	ret->statement_list = NewVector();
	ret->function_list = NewVector();
	return ret;
}

void DeleteILToplevel(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->import_list, il_top_level_import_delete);
	DeleteVector(self->namespace_list, il_top_level_DeleteNamespace);
	DeleteVector(self->statement_list, il_top_level_stmt_delete);
	DeleteVector(self->function_list, il_top_level_function_delete);
	MEM_FREE(self);
}

//private
static void il_top_level_import_delete(VectorItem item) {
	il_import* e = (il_import*)item;
	DeleteILImport(e);
}

static void il_top_level_DeleteNamespace(VectorItem item) {
	il_namespace* e = (il_namespace*)item;
	DeleteILNamespace(e);
}

static void il_top_level_function_delete(VectorItem item) {
	ILFunction* e = (ILFunction*)item;
	DeleteILFunction(e);
}

static void il_top_level_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}