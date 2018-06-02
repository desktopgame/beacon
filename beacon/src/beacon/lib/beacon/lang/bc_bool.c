#include "bc_bool.h"
#include "../../bc_library_impl.h"


void bc_bool_init() {
	namespace_* lang = namespace_lang();
	type* boolType = class_new_preload("Bool");
	namespace_add_type(lang, boolType);
}

type* bc_bool_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Bool");
}