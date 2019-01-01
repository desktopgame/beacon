#include "object.h"
#include <stdio.h>
#include "../../../util/mem.h"
#include "../../../util/string_buffer.h"
#include "../../../util/text.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

// proto
static void bc_Object_nativeToString(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env);
static void bc_Object_nativeReferenceEquals(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env);

void bc_InitObject() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* ObjectType = bc_NewPreloadClass(bc_InternString("Object"));
        bc_Class* ObjectClass = BC_TYPE2CLASS(ObjectType);
        bc_AddTypeNamespace(lang, ObjectType);
        bc_DefineNativeMethodClass(ObjectClass, "nativeToString",
                                   bc_Object_nativeToString);
        bc_DefineNativeMethodClass(ObjectClass, "nativeReferenceEquals",
                                   bc_Object_nativeReferenceEquals);
}

bc_Type* bc_GetObjectType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Object"));
}

// private
static void bc_Object_nativeToString(bc_Method* parent, bc_Frame* fr,
                                     bc_Enviroment* env) {
        bc_Object* self = (bc_Object*)bc_AtVector(fr->VariableTable, 0);
        bc_Buffer* sb = bc_NewBuffer();
        bc_AppendfBuffer(sb, "%p", self);
        char* str = bc_ReleaseBuffer(sb);
        bc_Object* ret = (bc_Object*)bc_NewString(str);
        bc_PushVector(fr->ValueStack, ret);
        MEM_FREE(str);
}

static void bc_Object_nativeReferenceEquals(bc_Method* parent, bc_Frame* fr,
                                            bc_Enviroment* env) {
        bc_Object* a = (bc_Object*)bc_AtVector(fr->VariableTable, 1);
        bc_Object* b = (bc_Object*)bc_AtVector(fr->VariableTable, 2);
        bc_PushVector(fr->ValueStack, bc_GetBoolObject(a == b));
}