#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_bool_nativeBitAnd(bc_Method* parent, Frame* fr, Enviroment* env);

bc_Object* NewBool(bool value) {
	Bool* ret = bc_ConstructObject(sizeof(Bool), BC_GENERIC_BOOL);
	ret->Value = value;
	return (bc_Object*)ret;
}

void InitBool() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* boolType = NewPreloadClass(InternString("Bool"));
	Class* boolClass = BC_TYPE2CLASS(boolType);
	boolType->AllocSize = sizeof(Bool);
	bc_AddTypeNamespace(lang, boolType);
	DefineNativeMethodClass(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	DefineNativeMethodClass(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

bc_Type* GetBoolType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	bc_Object* a = AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(bc_ObjectToBool(self) | bc_ObjectToBool(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_bool_nativeBitAnd(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	bc_Object* a = AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(bc_ObjectToBool(self) & bc_ObjectToBool(a));
	PushVector(fr->ValueStack, ret);
}