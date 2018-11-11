#include "bc_null.h"
#include "../../bc_library_impl.h"


void InitNull() {
	Namespace* lang = GetLangNamespace();
	Type* nullType = NewPreloadClass(InternString("Null"));
	AddTypeNamespace(lang, nullType);
}

Type* GetNullType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Null"));
}