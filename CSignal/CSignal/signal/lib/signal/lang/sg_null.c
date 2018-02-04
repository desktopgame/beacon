#include "sg_null.h"
#include "../../sg_library_impl.h"

void sg_null_init() {
	namespace_* lang = namespace_lang();
	class_* nullClass = class_new_preload("Null");
	namespace_add_type(lang, type_wrap_class(nullClass));
}
