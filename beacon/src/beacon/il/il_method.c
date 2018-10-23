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

ILMethod * NewILMethod(StringView namev) {
	ILMethod* ret = (ILMethod*)MEM_MALLOC(sizeof(ILMethod));
	ret->namev = namev;
	ret->parameter_list = NewVector();
	ret->return_fqcn = NewGenericCache();
	ret->access = ACCESS_PUBLIC_T;
	ret->modifier = MODIFIER_NONE_T;
	ret->statement_list = NewVector();
	ret->GetParameterListType = NewVector();
	ret->no_stmt = false;
	return ret;
}

void DeleteILMethod(ILMethod * self) {
	if (self == NULL) {
		return;
	}
	DeleteGenericCache(self->return_fqcn);
	DeleteVector(self->parameter_list, ILMethod_DeleteParameter);
	DeleteVector(self->statement_list, ILMethod_stmt_delete);
	DeleteVector(self->GetParameterListType, ILMethod_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void ILMethod_DeleteParameter(VectorItem item) {
	il_parameter* e = (il_parameter*)item;
	DeleteILParameter(e);
}

static void ILMethod_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}

static void ILMethod_DeleteTypeParameter(VectorItem item) {
	il_type_parameter* e = (il_type_parameter*)item;
	DeleteILTypeParameter(e);
}