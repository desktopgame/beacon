#include "bc_null.h"
#include "../../bc_library_impl.h"


void InitBCNull() {
	namespace_* lang = GetLangNamespace();
	type* nullType = NewPreloadClass(InternString("Null"));
	AddTypeNamespace(lang, nullType);
}

type* GetBCNullType() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Null"));
}