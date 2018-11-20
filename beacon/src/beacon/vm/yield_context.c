#include "yield_context.h"
#include "../util/mem.h"
bc_YieldContext* bc_MallocYieldContext(const char* filename, int lineno) {
	bc_YieldContext* ret = (bc_YieldContext*)bc_MXMalloc(sizeof(bc_YieldContext), filename, lineno);
	ret->BackupVariableTable = NULL;
	ret->BackupValueStack = NULL;
	ret->VariableTable = NULL;
	ret->ValueStack = NULL;
	ret->YieldCount = -1;
	ret->YieldOffset = -1;
	ret->Length = -1;
	ret->Stock = NULL;
	ret->Source = NULL;
	ret->IsCached = false;
	return ret;
}

void bc_ClearBackupYieldContext(bc_YieldContext* self) {
	bc_DeleteVector(self->BackupVariableTable, bc_VectorDeleterOfNull);
	bc_DeleteVector(self->BackupValueStack, bc_VectorDeleterOfNull);
	self->BackupVariableTable = NULL;
	self->BackupValueStack = NULL;
}

void bc_DeleteYieldContext(bc_YieldContext* self) {
	bc_DeleteVector(self->BackupVariableTable, bc_VectorDeleterOfNull);
	bc_DeleteVector(self->BackupValueStack, bc_VectorDeleterOfNull);
	bc_DeleteVector(self->Parameters, bc_VectorDeleterOfNull);
	MEM_FREE(self);
}