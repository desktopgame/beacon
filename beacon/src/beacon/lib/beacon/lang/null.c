#include "null.h"
#include "../../bc_library_impl.h"

void bc_InitNull() {
        bc_Namespace* lang = bc_GetLangNamespace();
        bc_Type* nullType = bc_NewPreloadClass(bc_InternString("Null"));
        bc_AddTypeNamespace(lang, nullType);
}

bc_Type* bc_GetNullType() {
        bc_Namespace* lang = bc_GetLangNamespace();
        return bc_FindTypeFromNamespace(lang, bc_InternString("Null"));
}