#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_parameter.h"
#include "il_type_parameter.h"

//proto
static void ILMethod_DeleteParameter(bc_VectorItem item);
static void ILMethod_stmt_delete(bc_VectorItem item);
static void ILMethod_DeleteTypeParameter(bc_VectorItem item);

ILMethod * NewILMethod(bc_StringView name) {
	ILMethod* ret = (ILMethod*)MEM_MALLOC(sizeof(ILMethod));
	ret->Name = name;
	ret->Parameters = bc_NewVector();
	ret->ReturnGCache = bc_NewGenericCache();
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Statements = bc_NewVector();
	ret->TypeParameters = bc_NewVector();
	ret->IsNoStmt = false;
	return ret;
}

void DeleteILMethod(ILMethod * self) {
	if (self == NULL) {
		return;
	}
	bc_DeleteGenericCache(self->ReturnGCache);
	bc_DeleteVector(self->Parameters, ILMethod_DeleteParameter);
	bc_DeleteVector(self->Statements, ILMethod_stmt_delete);
	bc_DeleteVector(self->TypeParameters, ILMethod_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void ILMethod_DeleteParameter(bc_VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void ILMethod_stmt_delete(bc_VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void ILMethod_DeleteTypeParameter(bc_VectorItem item) {
	ILTypeParameter* e = (ILTypeParameter*)item;
	DeleteILTypeParameter(e);
}