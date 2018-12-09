#include "thread.h"
#include <assert.h>
#include "../env/script_context.h"
#include "../il/call_context.h"
#include "../util/mem.h"
#include "../vm/vm.h"
#include "../vm/vm_trace.h"

// proto
static void ScriptThread_trace_delete(bc_VectorItem item);
static bc_ScriptThread* bc_new_script_thread();
static void bc_delete_script_thread(bc_ScriptThread* self);
static GRecMutex gMutex;
static bc_Vector* gAllThread;
static void bc_lock();
static void bc_unlock();

static bc_ScriptThread* g_sg_main_thread = NULL;

void bc_InitScriptThread() {
        assert(g_sg_main_thread == NULL);
        gAllThread = bc_NewVector();
        g_sg_main_thread = bc_new_script_thread();
        g_sg_main_thread->Thread = g_thread_self();
        bc_PushVector(gAllThread, g_sg_main_thread);
}

bc_ScriptThread* bc_GetCurrentScriptThread(bc_ScriptContext* sctx) {
        // ScriptContext* ctx = GetCurrentScriptContext();
        bc_lock();
        GThread* self = g_thread_self();
        bc_ScriptThread* ret = NULL;
        for (int i = 0; i < gAllThread->Length; i++) {
                bc_ScriptThread* e = bc_AtVector(gAllThread, i);
                if (e->Thread == self) {
                        ret = e;
                        break;
                }
        }
        bc_unlock();
        return ret;
}

void bc_SetScriptThreadFrameRef(bc_ScriptThread* self, bc_Frame* frame_ref) {
        // TODO:ここで同期をとる
        assert(frame_ref != NULL);
        assert(self->CCtx == NULL);
        self->IsVMCrushByException = false;
        self->IsVMDump = false;
        self->FrameRef = frame_ref;
        self->CCtx = bc_NewCallContext(CALL_TOP_T);
}

bc_Frame* bc_GetScriptThreadFrameRef(bc_ScriptThread* self) {
        // TODO:ここで同期をとる
        return self->FrameRef;
}

void bc_ReleaseScriptThreadFrameRef(bc_ScriptThread* self) {
        assert(self->CCtx != NULL);
        self->FrameRef = NULL;
        bc_DeleteCallContext(self->CCtx);
        self->CCtx = NULL;
}

bc_ScriptThread* bc_GetMainScriptThread() { return g_sg_main_thread; }

bc_CallContext* bc_GetScriptThreadContext() {
        return bc_GetCurrentScriptThread(NULL)->CCtx;
}

void bc_DestroyScriptThread() {
        bc_lock();
        bc_DeleteVector(gAllThread, bc_delete_script_thread);
        g_sg_main_thread = NULL;
        gAllThread = NULL;
        bc_unlock();
}
// private
static void ScriptThread_trace_delete(bc_VectorItem item) {
        bc_VMTrace* e = (bc_VMTrace*)item;
        bc_DeleteVMTrace(e);
}

static bc_ScriptThread* bc_new_script_thread() {
        bc_ScriptThread* ret =
            (bc_ScriptThread*)MEM_MALLOC(sizeof(bc_ScriptThread));
        ret->TraceStack = bc_NewVector();
        ret->FrameRef = NULL;
        ret->CCtx = NULL;
        ret->Thread = NULL;
        return ret;
}

static void bc_delete_script_thread(bc_ScriptThread* self) {
        bc_DeleteVector(self->TraceStack, ScriptThread_trace_delete);
        MEM_FREE(self);
}

static void bc_lock() { g_rec_mutex_lock(&gMutex); }

static void bc_unlock() { g_rec_mutex_unlock(&gMutex); }