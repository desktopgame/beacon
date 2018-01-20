#include "sg_int.h"
#include "../../sg_library_impl.h"

void sg_int_init() {
	namespace_* lang =  namespace_lang();
	class_* intClass = class_new_preload("Int");
	namespace_add_type(lang, type_wrap_class(intClass));
}
