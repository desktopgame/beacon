#include "defer_context.h"
#include "../util/mem.h"

bc_DeferContext* bc_NewDeferContext() {
	bc_DeferContext* ret = (bc_DeferContext*)MEM_MALLOC(sizeof(bc_DeferContext));
	ret->VariableTable = NULL;
	ret->Offset = NULL;
	return ret;
}

void bc_DeleteDeferContext(bc_DeferContext* self) {
	DeleteVector(self->VariableTable, VectorDeleterOfNull);
	MEM_FREE(self);
}