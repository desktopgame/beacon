#include "il_function.h"
#include "../env/generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_type_parameter.h"
#include "il_stmt_interface.h"
#include <stdio.h>

//proto
static void ILFunction_DeleteTypeParameter(bc_VectorItem item);
static void ILFunction_DeleteParameter(bc_VectorItem item);
static void ILFunction_stmt_delete(bc_VectorItem item);

ILFunction * NewILFunction(bc_StringView name) {
	ILFunction* ret = (ILFunction*)MEM_MALLOC(sizeof(ILFunction));
	ret->Name = name;
	ret->TypeParameters = bc_NewVector();
	ret->Parameters = bc_NewVector();
	ret->Statements = bc_NewVector();
	ret->ReturnGCache = bc_NewGenericCache();
	return ret;
}

void DeleteILFunction(ILFunction * self) {
	bc_DeleteVector(self->TypeParameters, ILFunction_DeleteTypeParameter);
	bc_DeleteVector(self->Parameters, ILFunction_DeleteParameter);
	bc_DeleteVector(self->Statements, ILFunction_stmt_delete);
	bc_DeleteGenericCache(self->ReturnGCache);
	MEM_FREE(self);
}

//private
static void ILFunction_DeleteTypeParameter(bc_VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}

static void ILFunction_DeleteParameter(bc_VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void ILFunction_stmt_delete(bc_VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}