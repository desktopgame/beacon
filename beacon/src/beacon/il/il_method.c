#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_parameter.h"
#include "il_type_parameter.h"

//proto
static void ILMethod_DeleteParameter(VectorItem item);
static void ILMethod_stmt_delete(VectorItem item);
static void ILMethod_DeleteTypeParameter(VectorItem item);

ILMethod * NewILMethod(StringView name) {
	ILMethod* ret = (ILMethod*)MEM_MALLOC(sizeof(ILMethod));
	ret->Name = name;
	ret->Parameters = NewVector();
	ret->ReturnGCache = NewGenericCache();
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Statements = NewVector();
	ret->TypeParameters = NewVector();
	ret->IsNoStmt = false;
	return ret;
}

void DeleteILMethod(ILMethod * self) {
	if (self == NULL) {
		return;
	}
	DeleteGenericCache(self->ReturnGCache);
	DeleteVector(self->Parameters, ILMethod_DeleteParameter);
	DeleteVector(self->Statements, ILMethod_stmt_delete);
	DeleteVector(self->TypeParameters, ILMethod_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void ILMethod_DeleteParameter(VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void ILMethod_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}

static void ILMethod_DeleteTypeParameter(VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}