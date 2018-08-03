#include "yield_context.h"
#include "../util/mem.h"

yield_context* yield_context_malloc(const char* filename, int lineno) {
	yield_context* ret = (yield_context*)mem_malloc(sizeof(yield_context), filename, lineno);
	ret->backup_ref_stack = NULL;
	ret->backup_value_stack = NULL;
	ret->vm_ref_stack = NULL;
	ret->vm_value_stack = NULL;
	ret->yield_count = -1;
	ret->yield_offset = -1;
	ret->len = -1;
	return ret;
}

void yield_context_delete(yield_context* self) {
	MEM_FREE(self);
}