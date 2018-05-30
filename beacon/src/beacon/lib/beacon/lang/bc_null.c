#include "bc_null.h"
#include "../../bc_library_impl.h"

static type* gBCNullType = NULL;

void bc_null_init() {
	namespace_* lang = namespace_lang();
	class_* nullClass = class_new_preload("Null");
	namespace_add_type(lang, type_wrap_class(nullClass));
}

type* bc_null_type() {
	if(gBCNullType == NULL) {
		namespace_* lang = namespace_lang();
		gBCNullType = namespace_get_type(lang, "Null");
	}
	return gBCNullType;
}