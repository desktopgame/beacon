#include "thread.h"
#include <glib.h>
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_thread_nativeStart(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_thread_nativeGetMainThread(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env);
static void bc_thread_nativeGetCurrentThread(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static gpointer bc_thread_body(gpointer data);

bc_Object* bc_NewThread(bc_ScriptThread* thread) {
        bc_Thread* ret = bc_ConstructObject(sizeof(bc_Thread),
                                            bc_GetThreadType()->GenericSelf);
        bc_ConnectThread((bc_Object*)ret, thread);
        return (bc_Object*)ret;
}

void bc_InitThread() {
        bc_Namespace* lang = bc_GetLangNamespace();
        bc_Type* threadType = bc_NewPreloadClass(bc_InternString("Thread"));
        bc_Class* threadClass = BC_TYPE2CLASS(threadType);
        threadType->AllocSize = sizeof(bc_Thread);
        bc_AddTypeNamespace(lang, threadType);
        bc_DefineNativeMethodClass(threadClass, "nativeInit",
                                   bc_thread_nativeInit);
        bc_DefineNativeMethodClass(threadClass, "nativeGetMainThread",
                                   bc_thread_nativeGetMainThread);
        bc_DefineNativeMethodClass(threadClass, "nativeGetCurrentThread",
                                   bc_thread_nativeGetCurrentThread);
}

bc_Type* bc_GetThreadType() {
        bc_Namespace* lang = bc_GetLangNamespace();
        return bc_FindTypeFromNamespace(lang, bc_InternString("Thread"));
}

void bc_ConnectThread(bc_Object* self, bc_ScriptThread* thr) {
        assert(thr->Owner == NULL);
        bc_Thread* obj = (bc_Thread*)self;
        obj->ScriptThreadRef = thr;
        thread->Owner = self;
}
// private
static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Thread* th = (bc_Thread*)self;
        bc_ScriptThread* thr = bc_CreateScriptThread();
        bc_ConnectThread(self, thr);
}

static void bc_thread_nativeStart(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Thread* th = (bc_Thread*)self;
        //メインスレッドに対して start は呼び出せない
        if (th == bc_GetMainScriptThread()->Thread) {
                bc_ThrowVM(fr, bc_NewSimpleException(
                                   fr, "can't be start a main thread."));
                return;
        }
        //スレッド生成時に渡された名前を取得
        bc_Type* ty = bc_GetThreadType();
        int temp = -1;
        bc_ResolveField(ty->Kind.Class, "name", &temp);
        assert(temp != -1);
        bc_Object* nameObj = bc_AtVector(self->Fields, temp);
        bc_Buffer* buffer = bc_GetRawString(nameObj);
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

static gpointer bc_thread_body(gpointer data) {
        bc_Thread* th = (bc_Thread*)data;
        return NULL;
}