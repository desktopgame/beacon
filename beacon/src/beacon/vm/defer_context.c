#include "defer_context.h"
#include "../util/mem.h"

DeferContext* NewDeferContext() {
	DeferContext* ret = (DeferContext*)MEM_MALLOC(sizeof(DeferContext));
	ret->VariableTable = NULL;
	ret->Offset = NULL;
	return ret;
}

void DeleteDeferContext(DeferContext* self) {
	DeleteVector(self->VariableTable, VectorDeleterOfNull);
	MEM_FREE(self);
}