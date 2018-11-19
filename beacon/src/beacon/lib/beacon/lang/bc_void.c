#include "bc_void.h"
#include "../../bc_library_impl.h"


void InitVoid() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* voidType = bc_NewPreloadClass(InternString("Void"));
	bc_Class* voidClass = BC_TYPE2CLASS(voidType);
	bc_AddTypeNamespace(lang, voidType);
}

bc_Type* GetVoidType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Void"));
}