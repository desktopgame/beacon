#include "symbol_entry.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/class.h"
symbol_entry * symbol_entry_new(const char * name) {
	symbol_entry* ret = (symbol_entry*)MEM_MALLOC(sizeof(symbol_entry));
	ret->index = 0;
	ret->type = NULL;
	return ret;
}

void symbol_entry_delete(symbol_entry * self) {
//	MEM_FREE(self->name);
	MEM_FREE(self);
}
