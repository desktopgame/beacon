#include "rec_mutex.h"
#include "../../../env/heap.h"
#include "../../../vm/script_thread.h"

static void bc_rec_mutex_nativeInit(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_rec_mutex_nativeLock(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);
static void bc_rec_mutex_nativeUnlock(bc_Method* parent, bc_Frame* fr,
                                      bc_Enviroment* env);
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]);

bc_Object* bc_NewRecMutex() {
        bc_RecMutex* ret = MEM_MALLOC(sizeof(bc_RecMutex));
        ret->Super.OnMessage = handle_obj_message;
        ret->Stack = 0;
        g_rec_mutex_init(&ret->Mutex);
        return ret;
}

void bc_InitRecMutex() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* recMutexType = bc_NewPreloadClass(bc_InternString("RecMutex"));
        bc_Class* recMutexClass = BC_TYPE2CLASS(recMutexType);
        recMutexType->AllocSize = sizeof(bc_RecMutex);
        bc_AddTypeNamespace(lang, recMutexType);
        bc_DefineNativeMethodClass(recMutexClass, "nativeInit",
                                   bc_rec_mutex_nativeInit);
        bc_DefineNativeMethodClass(recMutexClass, "nativeLock",
                                   bc_rec_mutex_nativeLock);
        bc_DefineNativeMethodClass(recMutexClass, "nativeUnlock",
                                   bc_rec_mutex_nativeUnlock);
}

bc_Type* bc_GetRecMutexType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("RecMutex"));
}
// private
static void bc_rec_mutex_nativeInit(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_RecMutex* self = bc_AtVector(fr->VariableTable, 0);
        self->Super.OnMessage = handle_obj_message;
        self->Stack = 0;
        g_mutex_init(&self->Mutex);
}
static void bc_rec_mutex_nativeLock(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_RecMutex* self = bc_AtVector(fr->VariableTable, 0);
        bool ret = false;
        if (self->Stack > 0) {
                ret = bc_BeginSyncHeap();
        }
        self->Stack++;
        g_rec_mutex_lock(&self->Mutex);
}
static void bc_rec_mutex_nativeUnlock(bc_Method* parent, bc_Frame* fr,
                                      bc_Enviroment* env) {
        bc_RecMutex* self = bc_AtVector(fr->VariableTable, 0);
        self->Stack--;
        if (self->Stack > 0) {
                bc_EndSyncHeap();
        }
        g_rec_mutex_unlock(&self->Mutex);
}
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc,
                                bc_ObjectMessageArgument argv[]) {
        return bc_HandleObjectMessage(self, msg, argc, argv);
}