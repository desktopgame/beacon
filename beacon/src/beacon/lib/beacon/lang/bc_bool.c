#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(method* parent, frame* fr, enviroment* env);
static void bc_bool_nativeBitAnd(method* parent, frame* fr, enviroment* env);

void bc_bool_init() {
	namespace_* lang = GetLangNamespace();
	type* boolType = class_new_preload(InternString("Bool"));
	class_* boolClass = TYPE2CLASS(boolType);
	AddTypeNamespace(lang, boolType);
	class_define_native_method(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	class_define_native_method(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

type* bc_bool_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Bool"));
}
//private
static void bc_bool_nativeBitOr(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.bool_ | a->u.bool_);
	PushVector(fr->value_stack, ret);
}

static void bc_bool_nativeBitAnd(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.bool_ & a->u.bool_);
	PushVector(fr->value_stack, ret);
}