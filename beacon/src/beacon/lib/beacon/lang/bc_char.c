#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env);

void bc_char_init() {
	namespace_* lang = namespace_lang();
	class_* charClass = class_new_preload("Char");
	namespace_add_type(lang, type_wrap_class(charClass));
	class_define_native_method(charClass, "nativeInit", bc_char_nativeInit);
}

//private
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* ch = vector_at(fr->ref_stack, 1);

	self->u.char_ = ch->u.char_;
	self->tag = object_char;
}