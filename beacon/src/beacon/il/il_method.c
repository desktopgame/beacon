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

bc_ILMethod * bc_NewILMethod(bc_StringView name) {
	bc_ILMethod* ret = (bc_ILMethod*)MEM_MALLOC(sizeof(bc_ILMethod));
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

void bc_DeleteILMethod(bc_ILMethod * self) {
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
	bc_ILParameter* e = (bc_ILParameter*)item;
	bc_DeleteILParameter(e);
}

static void ILMethod_stmt_delete(bc_VectorItem item) {
	bc_ILStatement* e = (bc_ILStatement*)item;
	bc_DeleteILStmt(e);
}

static void ILMethod_DeleteTypeParameter(bc_VectorItem item) {
	bc_ILTypeParameter* e = (bc_ILTypeParameter*)item;
	bc_DeleteILTypeParameter(e);
}