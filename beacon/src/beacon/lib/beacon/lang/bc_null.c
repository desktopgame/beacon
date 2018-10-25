#include "bc_null.h"
#include "../../bc_library_impl.h"


void InitBCNull() {
	Namespace* lang = GetLangNamespace();
	type* nullType = NewPreloadClass(InternString("Null"));
	AddTypeNamespace(lang, nullType);
}

type* GetBCNullType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Null"));
}