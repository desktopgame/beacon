#include "il_operator_overload.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"

static void DeleteILOperatorOverload_parameter(VectorItem item);
static void DeleteILOperatorOverload_stmt(VectorItem item);

ILOperatorOverload* NewILOperatorOverload(bc_OperatorType type) {
	ILOperatorOverload* ret = (ILOperatorOverload*)MEM_MALLOC(sizeof(ILOperatorOverload));
	ret->Type = type;
	ret->Parameters = NewVector();
	ret->Statements = NewVector();
	ret->ReturnGCache = bc_NewGenericCache();
	return ret;
}

void DeleteILOperatorOverload(ILOperatorOverload* self) {
	DeleteVector(self->Parameters, DeleteILOperatorOverload_parameter);
	DeleteVector(self->Statements, DeleteILOperatorOverload_stmt);
	bc_DeleteGenericCache(self->ReturnGCache);
	MEM_FREE(self);
}
//private
static void DeleteILOperatorOverload_parameter(VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void DeleteILOperatorOverload_stmt(VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}