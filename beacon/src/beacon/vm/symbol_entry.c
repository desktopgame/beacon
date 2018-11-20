#include "symbol_entry.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/type_interface.h"
#include "../env/generic_type.h"
bc_SymbolEntry * bc_NewSymbolEntry() {
	bc_SymbolEntry* ret = (bc_SymbolEntry*)MEM_MALLOC(sizeof(bc_SymbolEntry));
	ret->Index = 0;
	ret->GType = NULL;
	ret->ScopeDepth = 0;
	return ret;
}

void bc_DeleteSymbolEntry(bc_SymbolEntry * self) {
	MEM_FREE(self);
}
