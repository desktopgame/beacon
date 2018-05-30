#include "bc_int.h"
#include "../../bc_library_impl.h"

//proto
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env);
static type* gBCIntType = NULL;

void bc_int_init() {
	namespace_* lang =  namespace_lang();
	class_* intClass = class_new_preload("Int");
	namespace_add_type(lang, type_wrap_class(intClass));
	class_define_native_method(intClass, "nativeInit", bc_int_nativeInit);
}

type* bc_int_type() {
	if(gBCIntType == NULL) {
		namespace_* lang = namespace_lang();
		gBCIntType = namespace_get_type(lang, "Int");
	}
	return gBCIntType;
}
//private
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* i = vector_at(fr->ref_stack, 1);

	self->u.int_ = i->u.int_;
	self->tag = object_int;
}