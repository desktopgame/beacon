#include "monitor.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

void bc_InitMonitor() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* monitorType = bc_NewPreloadClass(bc_InternString("Monitor"));
        bc_Class* monitorClass = BC_TYPE2CLASS(monitorType);
        bc_AddTypeNamespace(lang, monitorType);
}

bc_Type* bc_GetMonitorType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Monitor"));
}