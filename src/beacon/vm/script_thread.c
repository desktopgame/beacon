#include "script_thread.h"
#include <assert.h>
#include "../env/heap.h"
#include "../env/script_context.h"
#include "../env/type_interface.h"
#include "../il/call_context.h"
#include "../lib/bc_library_interface.h"
#include "../util/mem.h"
#include "../vm/vm.h"
#include "../vm/vm_trace.h"

// proto
static void ScriptThread_trace_delete(bc_VectorItem item);
static bc_ScriptThread* bc_new_script_thread();
static void bc_delete_script_thread(bc_ScriptThread* self);
static GRecMutex gMutex;
static GRecMutex gActiveMutex;
static bc_Vector* gAllThread;
static void bc_lock();
static void bc_unlock();

static bc_ScriptThread* g_sg_main_thread = NULL;

void bc_InitScriptThread() {
        assert(g_sg_main_thread == NULL);
        gAllThread = bc_NewVector();
        g_sg_main_thread = bc_new_script_thread();
        g_sg_main_thread->Thread = g_thread_self();
        g_sg_main_thread->State = STHREAD_START;
        bc_lock();
        bc_PushVector(gAllThread, g_sg_main_thread);
        bc_unlock();
}

bc_ScriptThread* bc_AddScriptThread() {
        bc_ScriptThread* th = bc_new_script_thread();
        bc_lock();
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
        assert(ret != NULL);
        return ret;
}

void bc_ZombinizeScriptThread() {
        bc_lock();
        g_rec_mutex_lock(&gActiveMutex);
        bc_ScriptThread* sth = bc_GetCurrentScriptThread();
        sth->State = STHREAD_ZOMBIE;
        g_rec_mutex_unlock(&gActiveMutex);
        bc_unlock();
}

void bc_ExitScriptThread(bc_ScriptThread* self) {
        bc_lock();
        g_rec_mutex_lock(&gActiveMutex);
        assert(self->State == STHREAD_ZOMBIE);
        // bc_ScriptThread* cur = bc_GetCurrentScriptThread();
        assert(self != NULL);
        bc_RemoveVector(gAllThread, bc_FindVector(gAllThread, self));
        g_rec_mutex_unlock(&gActiveMutex);
        if (self->Thread != NULL) {
                g_thread_unref(self->Thread);
                self->Thread = NULL;
        }
        bc_unlock();
        bc_delete_script_thread(self);
}

void bc_StartScriptThread(bc_ScriptThread* self, bc_Object* threadObj,
                          GThreadFunc func, gpointer data) {
        g_rec_mutex_lock(&gActiveMutex);
        bc_lock();
        //スレッド生成時に渡された名前を取得
        bc_Type* ty = bc_GetThreadType();
        int temp = -1;
        bc_ResolveField(ty->Kind.Class, bc_InternString("name"), &temp);
        assert(temp != -1);
        bc_Object* nameObj = bc_AtVector(threadObj->Fields, temp);
        bc_Buffer* buffer = bc_GetRawString(nameObj);
        //スレッドを開始
        ((bc_Thread*)threadObj)->ScriptThreadRef = self;
        GThread* gth = g_thread_new(buffer->Text, func, data);
        self->Thread = gth;
        self->State = STHREAD_START;
        bc_unlock();
        g_rec_mutex_unlock(&gActiveMutex);
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
        return bc_GetCurrentScriptThread()->CCtx;
}

void bc_DestroyScriptThread() {
        bc_lock();
        bc_DeleteVector(gAllThread, bc_delete_script_thread);
        g_sg_main_thread = NULL;
        gAllThread = NULL;
        bc_unlock();
}

int bc_GetScriptThreadCount() {
        g_rec_mutex_lock(&gMutex);
        int ret = gAllThread->Length;
        g_rec_mutex_unlock(&gMutex);
        return ret;
}

int bc_GetActiveScriptThreadCount() {
        g_rec_mutex_lock(&gActiveMutex);
        bc_ScriptThread* main = bc_GetMainScriptThread();
        int count = 0;
        for (int i = 0; i < gAllThread->Length; i++) {
                bc_ScriptThread* e = bc_AtVector(gAllThread, i);
                bc_ScriptThreadState stat = e->State;
                if (stat == STHREAD_START) {
                        count++;
                }
        }
        g_rec_mutex_unlock(&gActiveMutex);
        return count;
}

bc_ScriptThread* bc_GetScriptThreadAt(int index) {
        return bc_AtVector(gAllThread, index);
}

void bc_LockScriptThread() { bc_lock(); }

void bc_UnlockScriptThread() { bc_unlock(); }

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
        ret->State = STHREAD_NONE;
        return ret;
}

static void bc_delete_script_thread(bc_ScriptThread* self) {
        bc_DeleteVector(self->TraceStack, ScriptThread_trace_delete);
        bc_DeleteVector(self->ScriptContextRefAll, bc_VectorDeleterOfNull);
        MEM_FREE(self);
}

static void bc_lock() { g_rec_mutex_lock(&gMutex); }

static void bc_unlock() { g_rec_mutex_unlock(&gMutex); }