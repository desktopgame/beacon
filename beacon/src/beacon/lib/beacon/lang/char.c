#include "char.h"
#include "../../bc_library_impl.h"

// proto
static void bc_char_nativeInit(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_char_nativeToInt(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);

bc_Object* bc_NewChar(char value) {
        bc_Char* ret = bc_ConstructObject(sizeof(bc_Char), BC_GENERIC_CHAR);
        ret->Value = value;
        return (bc_Object*)ret;
}

void bc_InitChar() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* charType = bc_NewPreloadClass(bc_InternString("Char"));
        bc_Class* charClass = BC_TYPE2CLASS(charType);
        charType->AllocSize = sizeof(bc_Char);
        bc_AddTypeNamespace(lang, charType);
        bc_DefineNativeMethodClass(charClass, "nativeInit", bc_char_nativeInit);
        bc_DefineNativeMethodClass(charClass, "nativeToInt",
                                   bc_char_nativeToInt);
}

bc_Type* bc_GetCharType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Char"));
}

// private
#define CHAR_VALUE(obj) (((bc_Char*)obj)->Value)
static void bc_char_nativeInit(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* ch = bc_AtVector(fr->VariableTable, 1);

        CHAR_VALUE(self) = CHAR_VALUE(ch);
        // self->Tag = OBJECT_CHAR_T;
}

static void bc_char_nativeToInt(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_PushVector(fr->ValueStack, bc_GetIntObject((int)CHAR_VALUE(self)));
}