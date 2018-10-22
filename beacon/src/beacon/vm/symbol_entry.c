#include "symbol_entry.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/type_interface.h"
#include "../env/generic_type.h"
SymbolEntry * NewSymbolEntry() {
	SymbolEntry* ret = (SymbolEntry*)MEM_MALLOC(sizeof(SymbolEntry));
	ret->Index = 0;
	ret->GType = NULL;
	ret->ScopeDepth = 0;
	return ret;
}

void DeleteSymbolEntry(SymbolEntry * self) {
	MEM_FREE(self);
}
