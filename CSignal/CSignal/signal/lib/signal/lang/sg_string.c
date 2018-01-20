#include "sg_string.h"
#include "../../sg_library_impl.h"

void sg_string_init() {
	namespace_* lang = namespace_lang();
	class_* stringClass = class_new_preload("String");
	namespace_add_type(lang, type_wrap_class(stringClass));
}
