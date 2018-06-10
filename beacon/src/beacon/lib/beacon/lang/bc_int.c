#include "bc_int.h"
#include "../../bc_library_impl.h"

//proto
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeEquals(method* parent, frame* fr, enviroment* env);

void bc_int_init() {
	namespace_* lang =  namespace_lang();
	type* intType = class_new_preload("Int");
	class_* intClass = TYPE2CLASS(intType);
	namespace_add_type(lang, intType);
	class_define_native_method(intClass, "nativeInit", bc_int_nativeInit);
	class_define_native_method(intClass, "nativeEquals", bc_int_nativeEquals);
}

type* bc_int_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Int");
}
//private
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* i = vector_at(fr->ref_stack, 1);

	self->u.int_ = i->u.int_;
	self->tag = object_int;
}

static void bc_int_nativeEquals(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* i = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, BOOL2OBJ(OBJ2INT(self) == OBJ2INT(i)));
}