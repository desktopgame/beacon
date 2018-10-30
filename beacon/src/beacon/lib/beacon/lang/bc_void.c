#include "bc_void.h"
#include "../../bc_library_impl.h"


void InitBCVoid() {
	Namespace* lang = GetLangNamespace();
	Type* voidType = NewPreloadClass(InternString("Void"));
	Class* voidClass = TYPE2CLASS(voidType);
	AddTypeNamespace(lang, voidType);
}

Type* GetBCVoidType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Void"));
}