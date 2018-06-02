#include "bc_double.h"
#include "../../bc_library_impl.h"

//proto
static void bc_double_nativeInit(method* parent, frame* fr, enviroment* env);

void bc_double_init() {
	namespace_* lang = namespace_lang();
	type* doubleType = class_new_preload("Double");
	class_* doubleClass = TYPE2CLASS(doubleType);
	namespace_add_type(lang, doubleType);
	class_define_native_method(doubleClass, "nativeInit", bc_double_nativeInit);
}

type* bc_double_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Double");
}
//private
static void bc_double_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* d = vector_at(fr->ref_stack, 1);

	self->u.double_ = d->u.double_;
	self->tag = object_double;
}
