#include "sg_char.h"
#include "../../sg_library_impl.h"

void sg_char_init() {
	namespace_* lang = namespace_lang();
	class_* charClass = class_new_preload("Char");
	namespace_add_type(lang, type_wrap_class(charClass));
}
