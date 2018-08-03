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
	ret->stock = false;
	ret->stockObject = NULL;
	return ret;
}

void yield_context_clear_backup(yield_context* self) {
	vector_delete(self->backup_ref_stack, vector_deleter_null);
	vector_delete(self->backup_value_stack, vector_deleter_null);
	self->backup_ref_stack = NULL;
	self->backup_value_stack = NULL;
}

void yield_context_delete(yield_context* self) {
	vector_delete(self->backup_ref_stack, vector_deleter_null);
	vector_delete(self->backup_value_stack, vector_deleter_null);
	MEM_FREE(self);
}