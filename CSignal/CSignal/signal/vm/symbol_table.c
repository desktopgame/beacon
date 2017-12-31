#include "symbol_table.h"
#include "../util/mem.h"

symbol_table * symbol_table_new() {
	symbol_table* ret = (symbol_table*)MEM_MALLOC(sizeof(symbol_table));
	ret->count = 1;
	ret->map = tree_map_new();
	return ret;
}

int symbol_table_add(symbol_table* self, const char * name) {
	int data = tree_map_get(self->map, name);
	if (!data) {
		return data;
	}
	int ret = self->count;
	tree_map_put(self->map, name, self->count);
	self->count++;
	return ret;
}

void symbol_table_delete(symbol_table * self) {
	tree_map_delete(self->map, tree_map_deleter_null);
}
