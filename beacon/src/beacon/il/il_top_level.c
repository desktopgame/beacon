#include "il_top_level.h"
#include <stdio.h>
#include <stdlib.h>
#include "../util/mem.h"
#include "il_function.h"
#include "il_import.h"
#include "il_namespace.h"
#include "il_stmt_interface.h"

// proto
static void ILToplevel_import_delete(bc_VectorItem item);
static void ILToplevel_DeleteNamespace(bc_VectorItem item);
static void ILToplevel_function_delete(bc_VectorItem item);
static void ILToplevel_stmt_delete(bc_VectorItem item);

bc_ILToplevel* bc_NewILToplevel() {
        bc_ILToplevel* ret = (bc_ILToplevel*)MEM_MALLOC(sizeof(bc_ILToplevel));
        ret->ImportList = bc_NewVector();
        ret->NamespaceList = bc_NewVector();
        ret->StatementList = bc_NewVector();
        ret->FunctionList = bc_NewVector();
        return ret;
}

void bc_DeleteILToplevel(bc_ILToplevel* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteVector(self->ImportList, ILToplevel_import_delete);
        bc_DeleteVector(self->NamespaceList, ILToplevel_DeleteNamespace);
        bc_DeleteVector(self->StatementList, ILToplevel_stmt_delete);
        bc_DeleteVector(self->FunctionList, ILToplevel_function_delete);
        MEM_FREE(self);
}

// private
static void ILToplevel_import_delete(bc_VectorItem item) {
        bc_ILImport* e = (bc_ILImport*)item;
        bc_DeleteILImport(e);
}

static void ILToplevel_DeleteNamespace(bc_VectorItem item) {
        bc_ILNamespace* e = (bc_ILNamespace*)item;
        bc_DeleteILNamespace(e);
}

static void ILToplevel_function_delete(bc_VectorItem item) {
        bc_ILFunction* e = (bc_ILFunction*)item;
        bc_DeleteILFunction(e);
}

static void ILToplevel_stmt_delete(bc_VectorItem item) {
        bc_ILStatement* e = (bc_ILStatement*)item;
        bc_DeleteILStmt(e);
}