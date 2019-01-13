#include "condition_variable.h"
#include "../../../env/heap.h"
#include "../../../vm/script_thread.h"
#include "../../bc_library_interface.h"

// proto
static void bc_condition_variable_nativeInit(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static void bc_condition_variable_nativeWait(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env);
static void bc_condition_variable_nativeWaitTimed(bc_Method* parent,
                                                  bc_Frame* fr,
                                                  bc_Enviroment* env);
static void bc_condition_variable_nativeSignal(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env);
static void bc_condition_variable_nativeBroadcast(bc_Method* parent,
                                                  bc_Frame* fr,
                                                  bc_Enviroment* env);

bc_Object* bc_NewConditionVariable() {
        bc_ConditionVariable* ret =
            bc_ConstructObject(sizeof(bc_ConditionVariable),
                               bc_GetConditionVariableType()->GenericSelf);
        g_cond_init(&ret->Cond);
        return (bc_Object*)ret;
}

void bc_InitConditionVariable() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* conditionVariableType =
            bc_NewPreloadClass(bc_InternString("ConditionVariable"));
        bc_Class* conditionVariableClass = BC_TYPE2CLASS(conditionVariableType);
        conditionVariableType->AllocSize = sizeof(bc_ConditionVariable);
        bc_AddTypeNamespace(lang, conditionVariableType);
        bc_DefineNativeMethodClass(conditionVariableClass, "nativeInit",
                                   bc_condition_variable_nativeInit);
        bc_DefineNativeMethodClass(conditionVariableClass, "nativeWait",
                                   bc_condition_variable_nativeWait);
        bc_DefineNativeMethodClass(conditionVariableClass, "nativeWaitTimed",
                                   bc_condition_variable_nativeWaitTimed);
        bc_DefineNativeMethodClass(conditionVariableClass, "nativeSignal",
                                   bc_condition_variable_nativeSignal);
        bc_DefineNativeMethodClass(conditionVariableClass, "nativeBroadcast",
                                   bc_condition_variable_nativeBroadcast);
}

bc_Type* bc_GetConditionVariableType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang,
                                        bc_InternString("ConditionVariable"));
}
// private
static void bc_condition_variable_nativeInit(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env) {
        bc_ConditionVariable* self = bc_AtVector(fr->VariableTable, 0);
        g_cond_init(&self->Cond);
}
static void bc_condition_variable_nativeWait(bc_Method* parent, bc_Frame* fr,
                                             bc_Enviroment* env) {
        bc_ConditionVariable* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* sync = bc_AtVector(fr->VariableTable, 1);
        bc_BeginSyncHeap();
        if (sync->GType->CoreType == bc_GetMutexType()) {
                GMutex m = ((bc_Mutex*)sync)->Mutex;
                g_cond_wait(&self->Cond, &m);
        } else if (sync->GType->CoreType == bc_GetRecMutexType()) {
                GRecMutex rm = ((bc_RecMutex*)sync)->Mutex;
                g_rec_mutex_lock(&rm);
                g_cond_wait(&self->Cond, &rm);
                g_rec_mutex_unlock(&rm);
        }
        bc_EndHeapSafeInvoke();
}
static void bc_condition_variable_nativeWaitTimed(bc_Method* parent,
                                                  bc_Frame* fr,
                                                  bc_Enviroment* env) {
        bc_ConditionVariable* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* sync = bc_AtVector(fr->VariableTable, 1);
        bc_Long* timeout = bc_AtVector(fr->VariableTable, 2);
        gboolean gb = 1;
        if (sync->GType->CoreType == bc_GetMutexType()) {
                gb = g_cond_timed_wait(&self->Cond, &((bc_Mutex*)sync)->Mutex,
                                       timeout->Value);
        } else if (sync->GType->CoreType == bc_GetRecMutexType()) {
                gb = g_cond_timed_wait(
                    &self->Cond, &((bc_RecMutex*)sync)->Mutex, timeout->Value);
        }
        bc_PushVector(fr->ValueStack, bc_GetBoolObject(gb));
}
static void bc_condition_variable_nativeSignal(bc_Method* parent, bc_Frame* fr,
                                               bc_Enviroment* env) {
        bc_ConditionVariable* self = bc_AtVector(fr->VariableTable, 0);
        g_cond_signal(&self->Cond);
}
static void bc_condition_variable_nativeBroadcast(bc_Method* parent,
                                                  bc_Frame* fr,
                                                  bc_Enviroment* env) {
        bc_ConditionVariable* self = bc_AtVector(fr->VariableTable, 0);
        g_cond_broadcast(&self->Cond);
}