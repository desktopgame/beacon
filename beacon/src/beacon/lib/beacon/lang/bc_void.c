#include "bc_void.h"
#include "../../bc_library_impl.h"


void InitVoid() {
	Namespace* lang = GetLangNamespace();
	Type* voidType = NewPreloadClass(InternString("Void"));
	Class* voidClass = TYPE2CLASS(voidType);
	AddTypeNamespace(lang, voidType);
}

Type* GetVoidType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Void"));
}