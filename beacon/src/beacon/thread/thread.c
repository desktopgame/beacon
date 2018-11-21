#include "thread.h"
#include "../util/mem.h"
#include "../env/script_context.h"
#include "../vm/vm_trace.h"
#include "../vm/vm.h"
#include "../il/call_context.h"
#include <assert.h>

//proto
static void ScriptThread_trace_delete(bc_VectorItem item);

static bc_ScriptThread* g_sg_main_thread = NULL;

void bc_LaunchScriptThread() {
	assert(g_sg_main_thread == NULL);
	g_sg_main_thread = bc_NewScriptThread();
}

bc_ScriptThread * bc_NewScriptThread() {
	bc_ScriptThread* ret = (bc_ScriptThread*)MEM_MALLOC(sizeof(bc_ScriptThread));
	ret->TraceStack = bc_NewVector();
	ret->FrameRef = NULL;
	ret->CCtx = NULL;
	return ret;
}

bc_ScriptThread * bc_GetCurrentScriptThread(bc_ScriptContext* sctx) {
	//ScriptContext* ctx = GetCurrentScriptContext();
	assert(sctx != NULL);
	//TODO:今は仮実装なのでちゃんと現在のスレッドを返すようにする
	bc_ScriptThread* ret = (bc_ScriptThread*)bc_AtVector(sctx->ThreadList, 0);
	return ret;
}

void bc_ClearScriptThread(bc_ScriptThread* self) {
	while (!bc_IsEmptyStack(self->TraceStack)) {
		bc_VMTrace* trace = (bc_VMTrace*)bc_PopVector(self->TraceStack);
		bc_DeleteVMTrace(trace);
	}
}

void bc_DeleteScriptThread(bc_ScriptThread * self) {
	bc_DeleteVector(self->TraceStack, ScriptThread_trace_delete);
	MEM_FREE(self);
}

void bc_SetScriptThreadFrameRef(bc_ScriptThread * self, bc_Frame* frame_ref) {
	//TODO:ここで同期をとる
	assert(frame_ref != NULL);
	assert(self->CCtx == NULL);
	self->IsVMCrushByException = false;
	self->IsVMDump = false;
	self->FrameRef = frame_ref;
	self->CCtx = bc_NewCallContext(CALL_TOP_T);
}

bc_Frame* bc_GetScriptThreadFrameRef(bc_ScriptThread * self) {
	//TODO:ここで同期をとる
	return self->FrameRef;
}

void bc_ReleaseScriptThreadFrameRef(bc_ScriptThread * self) {
	assert(self->CCtx != NULL);
	self->FrameRef = NULL;
	bc_DeleteCallContext(self->CCtx);
	self->CCtx = NULL;
}

bc_ScriptThread * bc_GetMainScriptThread() {
	return g_sg_main_thread;
}

bc_CallContext* bc_GetScriptThreadContext() {
	return g_sg_main_thread->CCtx;
}

void bc_DestroyScriptThread() {
	bc_DeleteScriptThread(g_sg_main_thread);
	g_sg_main_thread = NULL;
}
//private
static void ScriptThread_trace_delete(bc_VectorItem item) {
	bc_VMTrace* e = (bc_VMTrace*)item;
	bc_DeleteVMTrace(e);
}