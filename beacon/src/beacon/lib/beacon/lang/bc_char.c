#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env);
static void bc_char_nativeToInt(method* parent, frame* fr, enviroment* env);

void bc_char_init() {
	namespace_* lang = GetLangNamespace();
	type* charType = NewClass_preload(InternString("Char"));
	class_* charClass = TYPE2CLASS(charType);
	AddTypeNamespace(lang, charType);
	DefineNativeMethodClass(charClass, "nativeInit", bc_char_nativeInit);
	DefineNativeMethodClass(charClass, "nativeToInt", bc_char_nativeToInt);
}

type* bc_char_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Char"));
}

//private
static void bc_char_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* ch = AtVector(fr->ref_stack, 1);

	self->u.char_ = ch->u.char_;
	self->tag = OBJECT_CHAR_T;
}

static void bc_char_nativeToInt(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	PushVector(fr->value_stack, GetIntObject((int)self->u.char_));
}