#include "symbol_entry.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/type_interface.h"
#include "../env/generic_type.h"
symbol_entry * symbol_entry_new(const char * name) {
	symbol_entry* ret = (symbol_entry*)MEM_MALLOC(sizeof(symbol_entry));
	ret->index = 0;
	ret->gtype = NULL;
	return ret;
}

void symbol_entry_delete(symbol_entry * self) {
//	MEM_FREE(self->name);
//	generic_type_delete(self->gtype);
	MEM_FREE(self);
}
