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
static void symbol_table_delete_entry(NumericMapKey key, NumericMapItem item);
static void symbol_table_dump_entry(NumericMapKey key, NumericMapItem item);

symbol_table * symbol_table_new() {
	symbol_table* ret = (symbol_table*)MEM_MALLOC(sizeof(symbol_table));
	ret->count = 1;
	ret->map = NewNumericMap();
	ret->scope_depth = 0;
	return ret;
}

symbol_entry* symbol_table_entry(symbol_table* self, generic_type* gtp, string_view namev) {
	NumericMap* data = GetNumericMapCell(self->map, namev);
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
	e->scope_depth = self->scope_depth;
	PutNumericMap(self->map, namev, e);
	self->count++;
	return e;
}

bool symbol_table_contains(symbol_table* self, string_view namev) {
	return GetNumericMapCell(self->map, namev) != NULL;
}

void symbol_table_dump(symbol_table* self) {
	EachNumericMap(self->map, symbol_table_dump_entry);
}

void symbol_table_delete(symbol_table * self) {
	DeleteNumericMap(self->map, symbol_table_delete_entry);
	MEM_FREE(self);
}

//private
static void symbol_table_delete_entry(NumericMapKey key, NumericMapItem item) {
	symbol_entry* e = (symbol_entry*)item;
	symbol_entry_delete(e);
}
static void symbol_table_dump_entry(NumericMapKey key, NumericMapItem item) {
	printf("[%s] = %d\n", Ref2Str(key), ((symbol_entry*)item)->index);
}