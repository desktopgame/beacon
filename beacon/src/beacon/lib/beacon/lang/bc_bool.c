#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(Method* parent, Frame* fr, Enviroment* env);
static void bc_bool_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env);

Object* NewBool(bool value) {
	Bool* ret = ConstructObject(sizeof(Bool), GENERIC_BOOL);
	ret->Value = value;
	return (Object*)ret;
}

void InitBool() {
	Namespace* lang = GetLangNamespace();
	Type* boolType = NewPreloadClass(InternString("Bool"));
	Class* boolClass = TYPE2CLASS(boolType);
	boolType->AllocSize = sizeof(Bool);
	AddTypeNamespace(lang, boolType);
	DefineNativeMethodClass(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	DefineNativeMethodClass(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

Type* GetBoolType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(ObjectToBool(self) | ObjectToBool(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_bool_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(ObjectToBool(self) & ObjectToBool(a));
	PushVector(fr->ValueStack, ret);
}