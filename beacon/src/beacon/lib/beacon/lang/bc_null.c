#include "bc_null.h"
#include "../../bc_library_impl.h"


void InitBCNull() {
	Namespace* lang = GetLangNamespace();
	Type* nullType = NewPreloadClass(InternString("Null"));
	AddTypeNamespace(lang, nullType);
}

Type* GetBCNullType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Null"));
}