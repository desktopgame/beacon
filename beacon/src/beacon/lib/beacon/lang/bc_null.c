#include "bc_null.h"
#include "../../bc_library_impl.h"


void InitNull() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* nullType = bc_NewPreloadClass(InternString("Null"));
	bc_AddTypeNamespace(lang, nullType);
}

bc_Type* GetNullType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Null"));
}