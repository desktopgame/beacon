#include "bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_bool_nativeBitAnd(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);

bc_Object* bc_NewBool(bool value) {
	bc_Bool* ret = bc_ConstructObject(sizeof(bc_Bool), BC_GENERIC_BOOL);
	ret->Value = value;
	return (bc_Object*)ret;
}

void bc_InitBool() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* boolType = bc_NewPreloadClass(bc_InternString("Bool"));
	bc_Class* boolClass = BC_TYPE2CLASS(boolType);
	boolType->AllocSize = sizeof(bc_Bool);
	bc_AddTypeNamespace(lang, boolType);
	bc_DefineNativeMethodClass(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	bc_DefineNativeMethodClass(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

bc_Type* bc_GetBoolType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, bc_InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(bc_ObjectToBool(self) | bc_ObjectToBool(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_bool_nativeBitAnd(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(bc_ObjectToBool(self) & bc_ObjectToBool(a));
	bc_PushVector(fr->ValueStack, ret);
}