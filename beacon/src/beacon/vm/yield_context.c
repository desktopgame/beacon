#include "yield_context.h"
#include "../util/mem.h"
YieldContext* MallocYieldContext(const char* filename, int lineno) {
	YieldContext* ret = (YieldContext*)mem_malloc(sizeof(YieldContext), filename, lineno);
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

void ClearBackupYieldContext(YieldContext* self) {
	DeleteVector(self->BackupVariableTable, VectorDeleterOfNull);
	DeleteVector(self->BackupValueStack, VectorDeleterOfNull);
	self->BackupVariableTable = NULL;
	self->BackupValueStack = NULL;
}

void DeleteYieldContext(YieldContext* self) {
	DeleteVector(self->BackupVariableTable, VectorDeleterOfNull);
	DeleteVector(self->BackupValueStack, VectorDeleterOfNull);
	DeleteVector(self->Parameters, VectorDeleterOfNull);
	MEM_FREE(self);
}