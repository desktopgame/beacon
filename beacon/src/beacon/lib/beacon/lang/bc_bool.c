#include "bc_bool.h"
#include "../../bc_library_impl.h"


void bc_bool_init() {
	namespace_* lang = namespace_lang();
	class_* boolClass = class_new_preload("Bool");
	namespace_add_type(lang, type_wrap_class(boolClass));
}

type* bc_bool_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Bool");
}