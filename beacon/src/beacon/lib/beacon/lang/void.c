#include "void.h"
#include "../../bc_library_impl.h"


void bc_InitVoid() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* voidType = bc_NewPreloadClass(bc_InternString("Void"));
	bc_Class* voidClass = BC_TYPE2CLASS(voidType);
	bc_AddTypeNamespace(lang, voidType);
}

bc_Type* bc_GetVoidType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, bc_InternString("Void"));
}