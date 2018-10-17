#include "symbol_table.h"
#include "../util/mem.h"
#include "symbol_entry.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
//#include "../env/generic_type.h"
#include <assert.h>
#include <string.h>
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void DeleteSymbolTable_entry(NumericMapKey key, NumericMapItem item);
static void DumpSymbolTable_entry(NumericMapKey key, NumericMapItem item);

symbol_table * NewSymbolTable() {
	symbol_table* ret = (symbol_table*)MEM_MALLOC(sizeof(symbol_table));
	ret->count = 1;
	ret->map = NewNumericMap();
	ret->scope_depth = 0;
	return ret;
}

symbol_entry* EntrySymbolTable(symbol_table* self, generic_type* gtp, string_view namev) {
	NumericMap* data = GetNumericMapCell(self->map, namev);
	if (data) {
		return ((symbol_entry*)data->Item);
	}
	//フィールドアクセスのために追加
	if (gtp == NULL) {
		return NULL;
	}
	int ret = self->count;
	symbol_entry* e = NewSymbolEntry();
	e->index = self->count;
	e->gtype = gtp;
	e->scope_depth = self->scope_depth;
	PutNumericMap(self->map, namev, e);
	self->count++;
	return e;
}

bool IsContainsSymbol(symbol_table* self, string_view namev) {
	return GetNumericMapCell(self->map, namev) != NULL;
}

void DumpSymbolTable(symbol_table* self) {
	EachNumericMap(self->map, DumpSymbolTable_entry);
}

void DeleteSymbolTable(symbol_table * self) {
	DeleteNumericMap(self->map, DeleteSymbolTable_entry);
	MEM_FREE(self);
}

//private
static void DeleteSymbolTable_entry(NumericMapKey key, NumericMapItem item) {
	symbol_entry* e = (symbol_entry*)item;
	DeleteSymbolEntry(e);
}
static void DumpSymbolTable_entry(NumericMapKey key, NumericMapItem item) {
	printf("[%s] = %d\n", Ref2Str(key), ((symbol_entry*)item)->index);
}