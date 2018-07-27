#include "symbol_table.h"
#include "../util/mem.h"
#include "symbol_entry.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
//#include "../env/generic_type.h"
#include <assert.h>
#include <string.h>
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void symbol_table_delete_entry(numeric_key key, numeric_map_item item);
static void symbol_table_dump_entry(numeric_key key, numeric_map_item item);

symbol_table * symbol_table_new() {
	symbol_table* ret = (symbol_table*)MEM_MALLOC(sizeof(symbol_table));
	ret->count = 1;
	ret->map = numeric_map_new();
	return ret;
}

symbol_entry* symbol_table_entry(symbol_table* self, generic_type* gtp, string_view namev) {
	numeric_map* data = numeric_map_cell(self->map, namev);
	if (data) {
		return ((symbol_entry*)data->item);
	}
	//フィールドアクセスのために追加
	if (gtp == NULL) {
		return NULL;
	}
	int ret = self->count;
	symbol_entry* e = symbol_entry_new();
	e->index = self->count;
	e->gtype = gtp;
	numeric_map_put(self->map, namev, e);
	self->count++;
	return e;
}

void symbol_table_dump(symbol_table* self) {
	numeric_map_each(self->map, symbol_table_dump_entry);
}

void symbol_table_delete(symbol_table * self) {
	numeric_map_delete(self->map, symbol_table_delete_entry);
	MEM_FREE(self);
}

//private
static void symbol_table_delete_entry(numeric_key key, numeric_map_item item) {
	symbol_entry* e = (symbol_entry*)item;
	symbol_entry_delete(e);
}
static void symbol_table_dump_entry(numeric_key key, numeric_map_item item) {
	text_printf("[%s] = %d\n", string_pool_ref2str(key), ((symbol_entry*)item)->index);
}