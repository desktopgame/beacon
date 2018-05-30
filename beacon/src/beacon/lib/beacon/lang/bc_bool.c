#include "bc_bool.h"
#include "../../bc_library_impl.h"

static type* gBCBoolType = NULL;

void bc_bool_init() {
	namespace_* lang = namespace_lang();
	class_* boolClass = class_new_preload("Bool");
	namespace_add_type(lang, type_wrap_class(boolClass));
}

type* bc_bool_type() {
	if(gBCBoolType == NULL) {
		namespace_* lang = namespace_lang();
		gBCBoolType = namespace_get_type(lang, "Bool");
	}
	return gBCBoolType;
}