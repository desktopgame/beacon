#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include "../vm/vm.h"
#include "../il/call_context.h"
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
	ret->frame_ref = NULL;
	ret->cctx = NULL;
	return ret;
}

sg_thread * sg_thread_current(script_context* sctx) {
	//script_context* ctx = script_context_get_current();
	assert(sctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	sg_thread* ret = (sg_thread*)vector_at(sctx->thread_vec, 0);
	return ret;
}

void sg_thread_clear(sg_thread* self) {
	while (!IsEmptyStack(self->trace_stack)) {
		vm_trace* trace = (vm_trace*)PopStack(self->trace_stack);
		vm_trace_delete(trace);
	}
}

void sg_thread_delete(sg_thread * self) {
	vector_delete(self->trace_stack, sg_thread_trace_delete);
	MEM_FREE(self);
}

void sg_thread_set_frame_ref(sg_thread * self, frame * frame_ref) {
	//TODO:ここで同期をとる
	assert(frame_ref != NULL);
	assert(self->cctx == NULL);
	self->vm_crush_by_exception = false;
	self->vm_dump = false;
	self->frame_ref = frame_ref;
	self->cctx = call_context_new(call_top_T);
}

frame * sg_thread_get_frame_ref(sg_thread * self) {
	//TODO:ここで同期をとる
	return self->frame_ref;
}

void sg_thread_release_frame_ref(sg_thread * self) {
	assert(self->cctx != NULL);
	self->frame_ref = NULL;
	call_context_delete(self->cctx);
	self->cctx = NULL;
}

sg_thread * sg_thread_main() {
	return g_sg_main_thread;
}

call_context* sg_thread_context() {
	return g_sg_main_thread->cctx;
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