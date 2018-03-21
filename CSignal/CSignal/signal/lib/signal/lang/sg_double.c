#include "sg_double.h"
#include "../../sg_library_impl.h"

//proto
static void sg_double_nativeInit(method* parent, vm* vmc, enviroment* env);

void sg_double_init() {
	namespace_* lang = namespace_lang();
	class_* doubleClass = class_new_preload("Double");
	namespace_add_type(lang, type_wrap_class(doubleClass));
	class_define_native_method(doubleClass, "nativeInit", sg_double_nativeInit);
}
//private
static void sg_double_nativeInit(method* parent, vm* vmc, enviroment* env) {
	object* d = vector_pop(vmc->value_stack);
	object* self = vector_at(vmc->ref_stack, 0);

	self->u.double_ = d->u.double_;
	self->tag = object_double;
}
