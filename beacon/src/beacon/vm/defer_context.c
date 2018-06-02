#include "defer_context.h"
#include "../util/mem.h"
defer_context* defer_context_new() {
	defer_context* ret = (defer_context*)MEM_MALLOC(sizeof(defer_context));
	ret->bind = NULL;
	ret->offset = NULL;
	return ret;
}

void defer_context_delete(defer_context* self) {
	//label_delete(self->offset);
	vector_delete(self->bind, vector_deleter_null);
	MEM_FREE(self);
}