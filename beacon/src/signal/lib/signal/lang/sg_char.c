#include "sg_char.h"
#include "../../sg_library_impl.h"

//proto
static void sg_char_nativeInit(method* parent, vm* vmc, enviroment* env);

void sg_char_init() {
	namespace_* lang = namespace_lang();
	class_* charClass = class_new_preload("Char");
	namespace_add_type(lang, type_wrap_class(charClass));
	class_define_native_method(charClass, "nativeInit", sg_char_nativeInit);
}

//private
static void sg_char_nativeInit(method* parent, vm* vmc, enviroment* env) {
	object* ch = vector_pop(vmc->value_stack);
	object* self = vector_at(vmc->ref_stack, 0);

	self->u.char_ = ch->u.char_;
	self->tag = object_char;
}