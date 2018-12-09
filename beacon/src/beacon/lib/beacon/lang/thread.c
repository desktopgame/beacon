#include "thread.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_thread_nativeGetMainThread(bc_Method* parent, bc_Frame* fr,
                                          bc_Enviroment* env);
static void bc_thread_nativeGetCurrentThread(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);

bc_Object* bc_NewThread(bc_ScriptThread* thread) {
        bc_Thread* ret = bc_ConstructObject(sizeof(bc_Thread),
                                            bc_GetThreadType()->GenericSelf);
        assert(thread->Owner == NULL);
        ret->ScriptThread = thread;
        thread->Owner = (bc_Object*)ret;
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
// private
static void bc_thread_nativeInit(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {}

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