#include "sg_object.h"
#include "../../sg_library_impl.h"

void sg_object_init() {
	namespace_* lang = namespace_lang();
	class_* objClass = class_new_preload("Object");
	namespace_add_type(lang, type_wrap_class(objClass));
}
