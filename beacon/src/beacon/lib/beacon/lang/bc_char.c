#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env);
static type* gBCCharType = NULL;

void bc_char_init() {
	namespace_* lang = namespace_lang();
	class_* charClass = class_new_preload("Char");
	namespace_add_type(lang, type_wrap_class(charClass));
	class_define_native_method(charClass, "nativeInit", bc_char_nativeInit);
}

type* bc_char_type() {
	if(gBCCharType == NULL) {
		namespace_* lang = namespace_lang();
		gBCCharType = namespace_get_type(lang, "Char");
	}
	return gBCCharType;
}

//private
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* ch = vector_at(fr->ref_stack, 1);

	self->u.char_ = ch->u.char_;
	self->tag = object_char;
}