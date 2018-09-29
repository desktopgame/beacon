#include "defer_context.h"
#include "../util/mem.h"
defer_context* NewDeferContext() {
	defer_context* ret = (defer_context*)MEM_MALLOC(sizeof(defer_context));
	ret->variable_vec = NULL;
	ret->offset = NULL;
	return ret;
}

void DeleteDeferContext(defer_context* self) {
	DeleteVector(self->variable_vec, VectorDeleterOfNull);
	MEM_FREE(self);
}