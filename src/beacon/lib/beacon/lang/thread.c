#include "thread.h"
#include <glib.h>
#include "../../../env/heap.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"
#if __APPLE__
#include <unistd.h>
#endif

static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_thread_nativeStart(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_thread_nativeJoin(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_thread_nativeGetMainThread(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env);
static void bc_thread_nativeGetCurrentThread(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static void bc_thread_nativeSleep(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static gpointer bc_thread_body(gpointer data);
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]);

bc_Object* bc_NewThread(bc_ScriptThread* thread) {
        bc_Thread* ret = bc_ConstructObject(NULL, sizeof(bc_Thread),
                                            bc_GetThreadType()->GenericSelf);
        ret->Super.OnMessage = handle_obj_message;
        bc_ConnectThread((bc_Object*)ret, thread);
        return (bc_Object*)ret;
}

void bc_InitThread() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* threadType = bc_NewPreloadClass(bc_InternString("Thread"));
        bc_Class* threadClass = BC_TYPE2CLASS(threadType);
        threadType->AllocSize = sizeof(bc_Thread);
        bc_AddTypeNamespace(lang, threadType);
        bc_DefineNativeMethodClass(threadClass, "nativeInit",
                                   bc_thread_nativeInit);
        bc_DefineNativeMethodClass(threadClass, "nativeJoin",
                                   bc_thread_nativeJoin);
        bc_DefineNativeMethodClass(threadClass, "nativeStart",
                                   bc_thread_nativeStart);
        bc_DefineNativeMethodClass(threadClass, "nativeGetMainThread",
                                   bc_thread_nativeGetMainThread);
        bc_DefineNativeMethodClass(threadClass, "nativeGetCurrentThread",
                                   bc_thread_nativeGetCurrentThread);
        bc_DefineNativeMethodClass(threadClass, "nativeSleep",
                                   bc_thread_nativeSleep);
}

bc_Type* bc_GetThreadType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Thread"));
}

void bc_ConnectThread(bc_Object* self, bc_ScriptThread* thr) {
        assert(thr->Owner == NULL);
        bc_Thread* obj = (bc_Thread*)self;
        obj->ScriptThreadRef = thr;
        thr->Owner = self;
}
// private
static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Thread* th = (bc_Thread*)self;
        bc_ScriptThread* thr = bc_AddScriptThread();
        self->OnMessage = handle_obj_message;
        bc_ConnectThread(self, thr);
}

static void bc_thread_nativeStart(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Thread* th = (bc_Thread*)self;
        th->Env = env;
        //メインスレッドに対して start は呼び出せない
        if (th == bc_GetMainScriptThread()->Thread) {
                bc_ThrowVM(fr, bc_NewSimpleException(
                                   fr, "can't be start a main thread."));
                return;
        }
        bc_ScriptThread* sth = bc_AddScriptThread();
        bc_StartScriptThread(sth, self, bc_thread_body, self);
}

static void bc_thread_nativeJoin(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Thread* th = (bc_Thread*)self;
        bc_ScriptThread* sth = th->ScriptThreadRef;
        GThread* gth = sth->Thread;
        bc_BeginSyncHeap();
        g_thread_join(gth);
        sth->Thread = NULL;
        bc_EndSyncHeap();
}

static void bc_thread_nativeGetMainThread(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env) {
        bc_LockScriptThread();
        bc_ScriptThread* thr = bc_GetMainScriptThread();
        if (thr->Owner != NULL) {
                bc_PushVector(fr->ValueStack, thr->Owner);
                bc_UnlockScriptThread();
                return;
        }
        bc_Object* obj = bc_NewThread(thr);
        bc_PushVector(fr->ValueStack, obj);
        //スレッドの名前を適当に設定
        bc_Type* ty = bc_GetThreadType();
        int temp = -1;
        bc_ResolveField(ty->Kind.Class, "name", &temp);
        assert(temp != -1);
        bc_AssignVector(obj->Fields, temp, bc_NewString("Main"));

        bc_UnlockScriptThread();
}

static void bc_thread_nativeGetCurrentThread(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env) {
        bc_LockScriptThread();
        bc_ScriptThread* thr = bc_GetCurrentScriptThread();
        if (thr->Owner != NULL) {
                bc_PushVector(fr->ValueStack, thr->Owner);
                bc_UnlockScriptThread();
                return;
        }
        bc_Object* obj = bc_NewThread(thr);
        bc_PushVector(fr->ValueStack, obj);
        bc_UnlockScriptThread();
}

static void bc_thread_nativeSleep(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Long* lo = bc_AtVector(fr->VariableTable, 1);
        bc_BeginSyncHeap();
#if __APPLE__
        usleep(lo->Value);
#endif
        bc_EndSyncHeap();
}

static gpointer bc_thread_body(gpointer data) {
        bc_Thread* th = (bc_Thread*)data;
        bc_ScriptThread* sth = th->ScriptThreadRef;
        //新しいフレームで実行
        bc_Frame* fr = bc_NewFrame();
        // Thread#runnable を検索
        int temp = -1;
        bc_Field* runnableF = bc_ResolveField(
            bc_GetThreadType()->Kind.Class, bc_InternString("runnable"), &temp);
        assert(temp != -1);
        // Runnable#run を検索
        // FIXME:無駄遣い
        bc_Vector* typeargs = bc_NewVector();
        bc_CallContext* cctx = bc_NewCallContext(CALL_TOP_T);
        bc_Object* runnableObj = bc_AtVector(th->Super.Fields, temp);
        bc_Method* runM = bc_ResolveMethod(
            runnableObj->GType->CoreType->Kind.Class, bc_InternString("run"), 0,
            NULL, typeargs, cctx, &temp);
        assert(temp != -1);
        bc_DeleteCallContext(cctx);
        bc_DeleteVector(typeargs, bc_VectorDeleterOfNull);
        bc_AssignVector(fr->VariableTable, 0, runnableObj);
        bc_PushVector(fr->ValueStack, runnableObj);
        bc_SetScriptThreadFrameRef(sth, fr);
        // Runnable#run を実行
        bc_ExecuteMethod(runM, fr, th->Env);
        //スクリプトスレッドを破棄
        bc_ReleaseScriptThreadFrameRef(sth);
        bc_DeleteFrame(fr);
        bc_ZombinizeScriptThread();
        return NULL;
}

static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]) {
        if (msg == OBJECT_MSG_DELETE) {
                bc_Thread* th = self;
                bc_ExitScriptThread(th->ScriptThreadRef);
        }
        return bc_HandleObjectMessage(self, msg, argc, argv);
}