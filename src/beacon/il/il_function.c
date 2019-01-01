#include "il_function.h"
#include <stdio.h>
#include "../env/generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_type_parameter.h"

// proto
static void ILFunction_DeleteTypeParameter(bc_VectorItem item);
static void ILFunction_DeleteParameter(bc_VectorItem item);
static void ILFunction_stmt_delete(bc_VectorItem item);

bc_ILFunction* bc_NewILFunction(bc_StringView name) {
        bc_ILFunction* ret = (bc_ILFunction*)MEM_MALLOC(sizeof(bc_ILFunction));
        ret->Name = name;
        ret->TypeParameters = bc_NewVector();
        ret->Parameters = bc_NewVector();
        ret->Statements = bc_NewVector();
        ret->ReturnGCache = bc_NewGenericCache();
        return ret;
}

void bc_DeleteILFunction(bc_ILFunction* self) {
        bc_DeleteVector(self->TypeParameters, ILFunction_DeleteTypeParameter);
        bc_DeleteVector(self->Parameters, ILFunction_DeleteParameter);
        bc_DeleteVector(self->Statements, ILFunction_stmt_delete);
        bc_DeleteGenericCache(self->ReturnGCache);
        MEM_FREE(self);
}

// private
static void ILFunction_DeleteTypeParameter(bc_VectorItem item) {
        bc_ILTypeParameter* e = (bc_ILTypeParameter*)item;
        bc_DeleteILTypeParameter(e);
}

static void ILFunction_DeleteParameter(bc_VectorItem item) {
        bc_ILParameter* e = (bc_ILParameter*)item;
        bc_DeleteILParameter(e);
}

static void ILFunction_stmt_delete(bc_VectorItem item) {
        bc_ILStatement* e = (bc_ILStatement*)item;
        bc_DeleteILStmt(e);
}