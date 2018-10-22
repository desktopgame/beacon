#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(method* parent, Frame* fr, Enviroment* env);
static void bc_bool_nativeBitAnd(method* parent, Frame* fr, Enviroment* env);

void InitBCBool() {
	namespace_* lang = GetLangNamespace();
	type* boolType = NewPreloadClass(InternString("Bool"));
	class_* boolClass = TYPE2CLASS(boolType);
	AddTypeNamespace(lang, boolType);
	DefineNativeMethodClass(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	DefineNativeMethodClass(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

type* GetBCBoolType() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.bool_ | a->u.bool_);
	PushVector(fr->ValueStack, ret);
}

static void bc_bool_nativeBitAnd(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.bool_ & a->u.bool_);
	PushVector(fr->ValueStack, ret);
}