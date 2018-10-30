#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(Method* parent, Frame* fr, Enviroment* env);
static void bc_bool_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env);

void InitBCBool() {
	Namespace* lang = GetLangNamespace();
	Type* boolType = NewPreloadClass(InternString("Bool"));
	Class* boolClass = TYPE2CLASS(boolType);
	AddTypeNamespace(lang, boolType);
	DefineNativeMethodClass(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	DefineNativeMethodClass(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

Type* GetBCBoolType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.bool_ | a->u.bool_);
	PushVector(fr->ValueStack, ret);
}

static void bc_bool_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.bool_ & a->u.bool_);
	PushVector(fr->ValueStack, ret);
}