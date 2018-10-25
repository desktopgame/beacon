#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include "../vm/vm.h"
#include "../il/call_context.h"
#include <assert.h>

//proto
static void ScriptThread_trace_delete(VectorItem item);

static ScriptThread* g_sg_main_thread = NULL;

void LaunchSGThread() {
	assert(g_sg_main_thread == NULL);
	g_sg_main_thread = NewSGThread();
}

ScriptThread * NewSGThread() {
	ScriptThread* ret = (ScriptThread*)MEM_MALLOC(sizeof(ScriptThread));
	ret->TraceStack = NewVector();
	ret->FrameRef = NULL;
	ret->CCtx = NULL;
	return ret;
}

ScriptThread * GetCurrentSGThread(ScriptContext* sctx) {
	//ScriptContext* ctx = GetCurrentScriptContext();
	assert(sctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	ScriptThread* ret = (ScriptThread*)AtVector(sctx->ThreadList, 0);
	return ret;
}

void ClearSGThread(ScriptThread* self) {
	while (!IsEmptyStack(self->TraceStack)) {
		VMTrace* trace = (VMTrace*)PopVector(self->TraceStack);
		DeleteVMTrace(trace);
	}
}

void DeleteSGThread(ScriptThread * self) {
	DeleteVector(self->TraceStack, ScriptThread_trace_delete);
	MEM_FREE(self);
}

void SetSGThreadFrameRef(ScriptThread * self, Frame* frame_ref) {
	//TODO:ここで同期をとる
	assert(frame_ref != NULL);
	assert(self->CCtx == NULL);
	self->IsVMCrushByException = false;
	self->IsVMDump = false;
	self->FrameRef = frame_ref;
	self->CCtx = NewCallContext(CALL_TOP_T);
}

Frame* GetSGThreadFrameRef(ScriptThread * self) {
	//TODO:ここで同期をとる
	return self->FrameRef;
}

void ReleaseSGThreadFrameRef(ScriptThread * self) {
	assert(self->CCtx != NULL);
	self->FrameRef = NULL;
	DeleteCallContext(self->CCtx);
	self->CCtx = NULL;
}

ScriptThread * GetMainSGThread() {
	return g_sg_main_thread;
}

CallContext* GetSGThreadCContext() {
	return g_sg_main_thread->CCtx;
}

void DestroySGThread() {
	DeleteSGThread(g_sg_main_thread);
	g_sg_main_thread = NULL;
}
//private
static void ScriptThread_trace_delete(VectorItem item) {
	VMTrace* e = (VMTrace*)item;
	DeleteVMTrace(e);
}