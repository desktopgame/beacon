#include "mutex.h"
static void bc_mutex_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_mutex_nativeLock(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_mutex_nativeUnlock(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]);

bc_Object* bc_NewMutex() {
        bc_Mutex* ret = MEM_MALLOC(sizeof(bc_Mutex));
        ret->Super.OnMessage = handle_obj_message;
        g_mutex_init(&ret->Mutex);
        return ret;
}

void bc_InitMutex() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* mutexType = bc_NewPreloadClass(bc_InternString("Mutex"));
        bc_Class* mutexClass = BC_TYPE2CLASS(mutexType);
        mutexType->AllocSize = sizeof(bc_Mutex);
        bc_AddTypeNamespace(lang, mutexType);
        bc_DefineNativeMethodClass(mutexClass, "nativeInit",
                                   bc_mutex_nativeInit);
        bc_DefineNativeMethodClass(mutexClass, "nativeLock",
                                   bc_mutex_nativeLock);
        bc_DefineNativeMethodClass(mutexClass, "nativeUnlock",
                                   bc_mutex_nativeUnlock);
}

bc_Type* bc_GetMutexType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Mutex"));
}

// private
static void bc_mutex_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {}

static void bc_mutex_nativeLock(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Mutex* self = bc_AtVector(fr->VariableTable, 0);
        g_mutex_lock(&self->Mutex);
}
static void bc_mutex_nativeUnlock(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Mutex* self = bc_AtVector(fr->VariableTable, 0);
        g_mutex_unlock(&self->Mutex);
}
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]) {
        if (msg == OBJECT_MSG_DELETE) {
        }
        return bc_HandleObjectMessage(self, msg, argc, argv);
}