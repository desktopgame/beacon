#include "bc_void.h"
#include "../../bc_library_impl.h"


void bc_void_init() {
	namespace_* lang = namespace_lang();
	type* voidType = class_new_preload(InternString("Void"));
	class_* voidClass = TYPE2CLASS(voidType);
	namespace_add_type(lang, voidType);
}

type* bc_void_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, InternString("Void"));
}