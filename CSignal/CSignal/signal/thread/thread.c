#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include <assert.h>

static volatile sg_thread* g_sg_main_thread = NULL;

void sg_thread_launch() {
	assert(g_sg_main_thread == NULL);
	g_sg_main_thread = sg_thread_new();
}

sg_thread * sg_thread_new() {
	sg_thread* ret = (sg_thread*)MEM_MALLOC(sizeof(sg_thread));
	ret->trace_stack = vector_new();
	return ret;
}

sg_thread * sg_thread_current() {
	script_context* ctx = script_context_get_current();
	assert(ctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	return (sg_thread*)vector_at(ctx->threadVec, 0);
}

void sg_thread_clear(sg_thread* self) {
	while (!stack_empty(self->trace_stack)) {
		vm_trace* trace = (vm_trace*)stack_pop(self->trace_stack);
		vm_trace_delete(trace);
	}
}

void sg_thread_delete(sg_thread * self) {
}

sg_thread * sg_thread_main() {
	return g_sg_main_thread;
}

void sg_thread_destroy() {
	sg_thread_delete(g_sg_main_thread);
	g_sg_main_thread = NULL;
}
