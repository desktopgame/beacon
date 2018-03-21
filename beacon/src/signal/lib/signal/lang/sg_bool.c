#include "sg_bool.h"
#include "../../sg_library_impl.h"

void sg_bool_init() {
	namespace_* lang = namespace_lang();
	class_* boolClass = class_new_preload("Bool");
	namespace_add_type(lang, type_wrap_class(boolClass));
}
