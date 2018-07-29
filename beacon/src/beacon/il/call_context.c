#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"

call_context* call_context_malloc(const char* filename, int lineno) {
	call_context* ret = mem_malloc(sizeof(call_context), filename, lineno);
	ret->call_stack = vector_new();
	ret->space = NULL;
	ret->ty = NULL;
	return ret;
}

call_frame* call_context_push(call_context* self, call_frame_tag tag) {
	call_frame* fr = call_frame_new(tag);
	vector_push(self->call_stack, fr);
	return fr;
}

call_frame* call_context_top(call_context* self) {
	return vector_top(self->call_stack);
}

namespace_* call_context_namespace(call_context* self) {
	if(self->space != NULL) {
		return self->space;
	}
	return namespace_lang();
}

void call_context_pop(call_context* self) {
	call_frame* fr = vector_pop(self->call_stack);
	call_frame_delete(fr);
}

void call_context_delete(call_context* self) {
	MEM_FREE(self);
	vector_delete(self->call_stack, vector_deleter_null);
}