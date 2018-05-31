#include "bc_null.h"
#include "../../bc_library_impl.h"


void bc_null_init() {
	namespace_* lang = namespace_lang();
	class_* nullClass = class_new_preload("Null");
	namespace_add_type(lang, type_wrap_class(nullClass));
}

type* bc_null_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Null");
}