#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include "../vm/vm.h"
#include "../il/call_context.h"
#include <assert.h>

//proto
static void sg_thread_trace_delete(VectorItem item);

static volatile sg_thread* g_sg_main_thread = NULL;

void LaunchSGThread() {
	assert(g_sg_main_thread == NULL);
	g_sg_main_thread = NewSGThread();
}

sg_thread * NewSGThread() {
	sg_thread* ret = (sg_thread*)MEM_MALLOC(sizeof(sg_thread));
	ret->trace_stack = NewVector();
	ret->frame_ref = NULL;
	ret->cctx = NULL;
	return ret;
}

sg_thread * GetCurrentSGThread(script_context* sctx) {
	//script_context* ctx = GetCurrentScriptContext();
	assert(sctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	sg_thread* ret = (sg_thread*)AtVector(sctx->thread_vec, 0);
	return ret;
}

void ClearSGThread(sg_thread* self) {
	while (!IsEmptyStack(self->trace_stack)) {
		VMTrace* trace = (VMTrace*)PopStack(self->trace_stack);
		DeleteVMTrace(trace);
	}
}

void DeleteSGThread(sg_thread * self) {
	DeleteVector(self->trace_stack, sg_thread_trace_delete);
	MEM_FREE(self);
}

void SetSGThreadFrameRef(sg_thread * self, frame * frame_ref) {
	//TODO:ここで同期をとる
	assert(frame_ref != NULL);
	assert(self->cctx == NULL);
	self->vm_crush_by_exception = false;
	self->vm_dump = false;
	self->frame_ref = frame_ref;
	self->cctx = NewCallContext(CALL_TOP_T);
}

frame * GetSGThreadFrameRef(sg_thread * self) {
	//TODO:ここで同期をとる
	return self->frame_ref;
}

void ReleaseSGThreadFrameRef(sg_thread * self) {
	assert(self->cctx != NULL);
	self->frame_ref = NULL;
	DeleteCallContext(self->cctx);
	self->cctx = NULL;
}

sg_thread * GetMainSGThread() {
	return g_sg_main_thread;
}

call_context* GetSGThreadCContext() {
	return g_sg_main_thread->cctx;
}

void DestroySGThread() {
	DeleteSGThread(g_sg_main_thread);
	g_sg_main_thread = NULL;
}
//private
static void sg_thread_trace_delete(VectorItem item) {
	VMTrace* e = (VMTrace*)item;
	DeleteVMTrace(e);
}