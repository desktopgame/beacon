#include "bc_bool.h"
#include "../../bc_library_impl.h"

static void bc_bool_nativeBitOr(method* parent, frame* fr, enviroment* env);
static void bc_bool_nativeBitAnd(method* parent, frame* fr, enviroment* env);

void bc_bool_init() {
	namespace_* lang = namespace_lang();
	type* boolType = class_new_preload("Bool");
	class_* boolClass = TYPE2CLASS(boolType);
	namespace_add_type(lang, boolType);
	class_define_native_method(boolClass, "nativeBitOr", bc_bool_nativeBitOr);
	class_define_native_method(boolClass, "nativeBitAnd", bc_bool_nativeBitAnd);
}

type* bc_bool_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Bool");
}
//private
static void bc_bool_nativeBitOr(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.bool_ | a->u.bool_);
	vector_push(fr->value_stack, ret);
}

static void bc_bool_nativeBitAnd(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.bool_ & a->u.bool_);
	vector_push(fr->value_stack, ret);
}