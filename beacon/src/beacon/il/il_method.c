#include "il_method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_parameter.h"
#include "il_type_parameter.h"

//proto
static void il_method_DeleteParameter(VectorItem item);
static void il_method_stmt_delete(VectorItem item);
static void il_method_DeleteTypeParameter(VectorItem item);

il_method * NewILMethod(string_view namev) {
	il_method* ret = (il_method*)MEM_MALLOC(sizeof(il_method));
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

void DeleteILMethod(il_method * self) {
	if (self == NULL) {
		return;
	}
	DeleteGenericCache(self->return_fqcn);
	DeleteVector(self->parameter_list, il_method_DeleteParameter);
	DeleteVector(self->statement_list, il_method_stmt_delete);
	DeleteVector(self->GetParameterListType, il_method_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void il_method_DeleteParameter(VectorItem item) {
	il_parameter* e = (il_parameter*)item;
	DeleteILParameter(e);
}

static void il_method_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}

static void il_method_DeleteTypeParameter(VectorItem item) {
	il_type_parameter* e = (il_type_parameter*)item;
	DeleteILTypeParameter(e);
}