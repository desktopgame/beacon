#include "symbol_table.h"
#include "../util/mem.h"
#include "symbol_entry.h"
#include "../env/class.h"
#include <assert.h>

//proto
static void symbol_table_delete_entry(tree_item item);

symbol_table * symbol_table_new() {
	symbol_table* ret = (symbol_table*)MEM_MALLOC(sizeof(symbol_table));
	ret->count = 1;
	ret->map = tree_map_new();
	return ret;
}

symbol_entry* symbol_table_entry(symbol_table* self, class_* cls, const char * name) {
	tree_item data = tree_map_get(self->map, name);
	if (data) {
		return ((symbol_entry*)data);
	}
	assert(cls != NULL);
	int ret = self->count;
	symbol_entry* e = symbol_entry_new(name);
	e->index = self->count;
	e->type = cls;
	tree_map_put(self->map, name, e);
	self->count++;
	return e;
}

void symbol_table_delete(symbol_table * self) {
	tree_map_delete(self->map, symbol_table_delete_entry);
}

//private
static void symbol_table_delete_entry(tree_item item) {
	symbol_entry* e = (symbol_entry*)item;
	symbol_entry_delete(e);
}