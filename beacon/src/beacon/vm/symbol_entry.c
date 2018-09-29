#include "symbol_entry.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/type_interface.h"
#include "../env/generic_type.h"
symbol_entry * NewSymbolEntry() {
	symbol_entry* ret = (symbol_entry*)MEM_MALLOC(sizeof(symbol_entry));
	ret->index = 0;
	ret->gtype = NULL;
	ret->scope_depth = 0;
	return ret;
}

void DeleteSymbolEntry(symbol_entry * self) {
	MEM_FREE(self);
}
