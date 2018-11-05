#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(Method* parent, Frame* fr, Enviroment* env);
static void bc_char_nativeToInt(Method* parent, Frame* fr, Enviroment* env);

Char* NewChar(char value) {
	Char* ret = ConstructObject(sizeof(Char), GENERIC_CHAR);
	ret->Value = value;
	return ret;
}

void InitBCChar() {
	Namespace* lang = GetLangNamespace();
	Type* charType = NewPreloadClass(InternString("Char"));
	Class* charClass = TYPE2CLASS(charType);
	AddTypeNamespace(lang, charType);
	DefineNativeMethodClass(charClass, "nativeInit", bc_char_nativeInit);
	DefineNativeMethodClass(charClass, "nativeToInt", bc_char_nativeToInt);
}

Type* GetBCCharType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Char"));
}

//private
#define CHAR_VALUE(obj) (((Char*)obj)->Value)
static void bc_char_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* ch = AtVector(fr->VariableTable, 1);

	CHAR_VALUE(self) = CHAR_VALUE(ch);
	self->Tag = OBJECT_CHAR_T;
}

static void bc_char_nativeToInt(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	PushVector(fr->ValueStack, GetIntObject((int)CHAR_VALUE(self)));
}