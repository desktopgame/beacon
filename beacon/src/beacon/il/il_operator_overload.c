#include "il_operator_overload.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"

static void DeleteILOperatorOverload_parameter(bc_VectorItem item);
static void DeleteILOperatorOverload_stmt(bc_VectorItem item);

bc_ILOperatorOverload* bc_NewILOperatorOverload(bc_OperatorType type) {
	bc_ILOperatorOverload* ret = (bc_ILOperatorOverload*)MEM_MALLOC(sizeof(bc_ILOperatorOverload));
	ret->Type = type;
	ret->Parameters = bc_NewVector();
	ret->Statements = bc_NewVector();
	ret->ReturnGCache = bc_NewGenericCache();
	return ret;
}

void bc_DeleteILOperatorOverload(bc_ILOperatorOverload* self) {
	bc_DeleteVector(self->Parameters, DeleteILOperatorOverload_parameter);
	bc_DeleteVector(self->Statements, DeleteILOperatorOverload_stmt);
	bc_DeleteGenericCache(self->ReturnGCache);
	MEM_FREE(self);
}
//private
static void DeleteILOperatorOverload_parameter(bc_VectorItem item) {
	bc_ILParameter* e = (bc_ILParameter*)item;
	bc_DeleteILParameter(e);
}

static void DeleteILOperatorOverload_stmt(bc_VectorItem item) {
	bc_ILStatement* e = (bc_ILStatement*)item;
	bc_DeleteILStmt(e);
}