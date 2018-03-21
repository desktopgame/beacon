#include "sg_int.h"
#include "../../sg_library_impl.h"

//proto
static void sg_int_nativeInit(method* parent, vm* vmc, enviroment* env);

void sg_int_init() {
	namespace_* lang =  namespace_lang();
	class_* intClass = class_new_preload("Int");
	namespace_add_type(lang, type_wrap_class(intClass));
	class_define_native_method(intClass, "nativeInit", sg_int_nativeInit);
}
//private
static void sg_int_nativeInit(method* parent, vm* vmc, enviroment* env) {
	object* i = vector_pop(vmc->value_stack);
	object* self = vector_at(vmc->ref_stack, 0);

	self->u.int_ = i->u.int_;
	self->tag = object_int;
}