#include "bc_null.h"
#include "../../bc_library_impl.h"


void bc_null_init() {
	namespace_* lang = GetLangNamespace();
	type* nullType = class_new_preload(InternString("Null"));
	AddTypeNamespace(lang, nullType);
}

type* bc_null_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Null"));
}