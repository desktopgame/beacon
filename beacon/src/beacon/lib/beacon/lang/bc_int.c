#include "bc_int.h"
#include "../../bc_library_impl.h"

//proto
static void bc_int_nativeInit(method* parent, vm* vmc, enviroment* env);

void bc_int_init() {
	namespace_* lang =  namespace_lang();
	class_* intClass = class_new_preload("Int");
	namespace_add_type(lang, type_wrap_class(intClass));
	class_define_native_method(intClass, "nativeInit", bc_int_nativeInit);
}
//private
static void bc_int_nativeInit(method* parent, vm* vmc, enviroment* env) {
	object* self = vector_at(vmc->ref_stack, 0);
	object* i = vector_at(vmc->ref_stack, 1);

	self->u.int_ = i->u.int_;
	self->tag = object_int;
}