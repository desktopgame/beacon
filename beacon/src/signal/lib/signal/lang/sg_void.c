#include "sg_void.h"
#include "../../sg_library_impl.h"

void sg_void_init() {
	namespace_* lang = namespace_lang();
	class_* voidClass = class_new_preload("Void");
	namespace_add_type(lang, type_wrap_class(voidClass));
}
