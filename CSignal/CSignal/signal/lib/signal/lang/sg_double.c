#include "sg_double.h"
#include "../../sg_library_impl.h"

void sg_double_init() {
	namespace_* lang = namespace_lang();
	class_* doubleClass = class_new_preload("Double");
	namespace_add_type(lang, type_wrap_class(doubleClass));
}
