#include "bc_void.h"
#include "../../bc_library_impl.h"


void bc_void_init() {
	namespace_* lang = GetLangNamespace();
	type* voidType = NewPreloadClass(InternString("Void"));
	class_* voidClass = TYPE2CLASS(voidType);
	AddTypeNamespace(lang, voidType);
}

type* bc_void_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Void"));
}