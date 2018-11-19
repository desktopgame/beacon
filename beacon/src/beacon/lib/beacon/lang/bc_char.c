#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_char_nativeToInt(bc_Method* parent, Frame* fr, Enviroment* env);

bc_Object* NewChar(char value) {
	Char* ret = bc_ConstructObject(sizeof(Char), BC_GENERIC_CHAR);
	ret->Value = value;
	return (bc_Object*)ret;
}

void InitChar() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* charType = bc_NewPreloadClass(InternString("Char"));
	bc_Class* charClass = BC_TYPE2CLASS(charType);
	charType->AllocSize = sizeof(Char);
	bc_AddTypeNamespace(lang, charType);
	bc_DefineNativeMethodClass(charClass, "nativeInit", bc_char_nativeInit);
	bc_DefineNativeMethodClass(charClass, "nativeToInt", bc_char_nativeToInt);
}

bc_Type* GetCharType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Char"));
}

//private
#define CHAR_VALUE(obj) (((Char*)obj)->Value)
static void bc_char_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	bc_Object* ch = AtVector(fr->VariableTable, 1);

	CHAR_VALUE(self) = CHAR_VALUE(ch);
	//self->Tag = OBJECT_CHAR_T;
}

static void bc_char_nativeToInt(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	PushVector(fr->ValueStack, bc_GetIntObject((int)CHAR_VALUE(self)));
}