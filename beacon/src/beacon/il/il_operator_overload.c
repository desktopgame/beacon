#include "il_operator_overload.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"

static void DeleteILOperatorOverload_parameter(VectorItem item);
static void DeleteILOperatorOverload_stmt(VectorItem item);

ILOperatorOverload* NewILOperatorOverload(OperatorType type) {
	ILOperatorOverload* ret = (ILOperatorOverload*)MEM_MALLOC(sizeof(ILOperatorOverload));
	ret->op = type;
	ret->parameter_list = NewVector();
	ret->statement_list = NewVector();
	ret->return_fqcn = NewGenericCache();
	return ret;
}

void DeleteILOperatorOverload(ILOperatorOverload* self) {
	DeleteVector(self->parameter_list, DeleteILOperatorOverload_parameter);
	DeleteVector(self->statement_list, DeleteILOperatorOverload_stmt);
	DeleteGenericCache(self->return_fqcn);
	MEM_FREE(self);
}
//private
static void DeleteILOperatorOverload_parameter(VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void DeleteILOperatorOverload_stmt(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}