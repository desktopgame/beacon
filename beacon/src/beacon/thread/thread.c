#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include "../vm/vm.h"
#include <assert.h>

//proto
static void sg_thread_trace_delete(vector_item item);

static volatile sg_thread* g_sg_main_thread = NULL;

void sg_thread_launch() {
	assert(g_sg_main_thread == NULL);
	g_sg_main_thread = sg_thread_new();
}

sg_thread * sg_thread_new() {
	sg_thread* ret = (sg_thread*)MEM_MALLOC(sizeof(sg_thread));
	ret->trace_stack = vector_new();
	ret->vmRef = NULL;
	return ret;
}

sg_thread * sg_thread_current() {
	script_context* ctx = script_context_get_current();
	assert(ctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	return (sg_thread*)vector_at(ctx->thread_vec, 0);
}

void sg_thread_clear(sg_thread* self) {
	while (!stack_empty(self->trace_stack)) {
		vm_trace* trace = (vm_trace*)stack_pop(self->trace_stack);
		vm_trace_delete(trace);
	}
}

void sg_thread_delete(sg_thread * self) {
	vector_delete(self->trace_stack, sg_thread_trace_delete);
	MEM_FREE(self);
}

void sg_thread_set_vm_ref(sg_thread * self, vm * vmRef) {
	//TODO:ここで同期をとる
	assert(vmRef != NULL);
	self->vmRef = vmRef;
}

vm * sg_thread_get_vm_ref(sg_thread * self) {
	//TODO:ここで同期をとる
	return self->vmRef;
}

void sg_thread_release_vm_ref(sg_thread * self) {
	self->vmRef = NULL;
}

sg_thread * sg_thread_main() {
	return g_sg_main_thread;
}

void sg_thread_destroy() {
	sg_thread_delete(g_sg_main_thread);
	g_sg_main_thread = NULL;
}
//private
static void sg_thread_trace_delete(vector_item item) {
	vm_trace* e = (vm_trace*)item;
	vm_trace_delete(e);
}