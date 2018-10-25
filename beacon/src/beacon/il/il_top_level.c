#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_import.h"
#include "il_namespace.h"
#include "il_function.h"

//proto
static void ILToplevel_import_delete(VectorItem item);
static void ILToplevel_DeleteNamespace(VectorItem item);
static void ILToplevel_function_delete(VectorItem item);
static void ILToplevel_stmt_delete(VectorItem item);

ILToplevel* NewILToplevel() {
	ILToplevel* ret = (ILToplevel*)MEM_MALLOC(sizeof(ILToplevel));
	ret->import_list = NewVector();
	ret->Namespacelist = NewVector();
	ret->statement_list = NewVector();
	ret->function_list = NewVector();
	return ret;
}

void DeleteILToplevel(ILToplevel* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->import_list, ILToplevel_import_delete);
	DeleteVector(self->Namespacelist, ILToplevel_DeleteNamespace);
	DeleteVector(self->statement_list, ILToplevel_stmt_delete);
	DeleteVector(self->function_list, ILToplevel_function_delete);
	MEM_FREE(self);
}

//private
static void ILToplevel_import_delete(VectorItem item) {
	ILImport* e = (ILImport*)item;
	DeleteILImport(e);
}

static void ILToplevel_DeleteNamespace(VectorItem item) {
	ILNamespace* e = (ILNamespace*)item;
	DeleteILNamespace(e);
}

static void ILToplevel_function_delete(VectorItem item) {
	ILFunction* e = (ILFunction*)item;
	DeleteILFunction(e);
}

static void ILToplevel_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}