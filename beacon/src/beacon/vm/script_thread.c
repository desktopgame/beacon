#include "script_thread.h"
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
        bc_lock();
        bc_PushVector(gAllThread, g_sg_main_thread);
        bc_unlock();
}

bc_ScriptThread* bc_AddScriptThread() {
        bc_ScriptThread* th = bc_new_script_thread();
        bc_lock();
        bc_AttachScriptContext(
            th, bc_SelectedScriptContext(bc_GetMainScriptThread()));
        bc_PushVector(gAllThread, th);
        bc_unlock();
        return th;
}

bc_ScriptThread* bc_GetCurrentScriptThread() {
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

void bc_StartScriptThread(bc_ScriptThread* self, bc_Object* runnable) {}

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
        return bc_GetCurrentScriptThread()->CCtx;
}

void bc_DestroyScriptThread() {
        bc_lock();
        bc_DeleteVector(gAllThread, bc_delete_script_thread);
        g_sg_main_thread = NULL;
        gAllThread = NULL;
        bc_unlock();
}

void bc_LockScriptThread() { bc_lock(); }

int bc_GetScriptThreadCount() { return gAllThread->Length; }

bc_ScriptThread* bc_GetScriptThreadAt(int index) {
        return bc_AtVector(gAllThread, index);
}

void bc_UnlockScriptThread() { bc_unlock(); }

void bc_AttachScriptContext(bc_ScriptThread* self, bc_ScriptContext* script) {
        bc_ScriptThread* thr = self;
        assert(thr != NULL);
        assert(script->ThreadRef == NULL);
        if (thr->SelectedScriptContext == -1) {
                thr->SelectedScriptContext = 0;
        }
        script->ThreadRef = thr;
        bc_PushVector(thr->ScriptContextRefAll, script);
}

void bc_DetachScriptContext(bc_ScriptContext* script) {
        bc_ScriptThread* thr = script->ThreadRef;
        assert(thr != NULL);
        bc_ScriptContext* selected = bc_SelectedScriptContext(thr);
        if (selected == script) {
                thr->SelectedScriptContext = -1;
        }
        bc_RemoveVector(thr->ScriptContextRefAll,
                        bc_FindVector(thr->ScriptContextRefAll, script));
}

bc_ScriptContext* bc_SelectedScriptContext(bc_ScriptThread* self) {
        if (self->SelectedScriptContext == -1) {
                return NULL;
        }
        return bc_AtVector(self->ScriptContextRefAll,
                           self->SelectedScriptContext);
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
        ret->ScriptContextRefAll = bc_NewVector();
        ret->Owner = NULL;
        ret->SelectedScriptContext = -1;
        return ret;
}

static void bc_delete_script_thread(bc_ScriptThread* self) {
        bc_DeleteVector(self->TraceStack, ScriptThread_trace_delete);
        bc_DeleteVector(self->ScriptContextRefAll, bc_VectorDeleterOfNull);
        MEM_FREE(self);
}

static void bc_lock() { g_rec_mutex_lock(&gMutex); }

static void bc_unlock() { g_rec_mutex_unlock(&gMutex); }