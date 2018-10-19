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

SymbolTable * NewSymbolTable() {
	SymbolTable* ret = (SymbolTable*)MEM_MALLOC(sizeof(SymbolTable));
	ret->Count = 1;
	ret->VariableMap = NewNumericMap();
	ret->ScopeDepth = 0;
	return ret;
}

symbol_entry* EntrySymbolTable(SymbolTable* self, generic_type* gtp, StringView namev) {
	NumericMap* data = GetNumericMapCell(self->VariableMap, namev);
	if (data) {
		return ((symbol_entry*)data->Item);
	}
	//フィールドアクセスのために追加
	if (gtp == NULL) {
		return NULL;
	}
	int ret = self->Count;
	symbol_entry* e = NewSymbolEntry();
	e->index = self->Count;
	e->gtype = gtp;
	e->scope_depth = self->ScopeDepth;
	PutNumericMap(self->VariableMap, namev, e);
	self->Count++;
	return e;
}

bool IsContainsSymbol(SymbolTable* self, StringView namev) {
	return GetNumericMapCell(self->VariableMap, namev) != NULL;
}

void DumpSymbolTable(SymbolTable* self) {
	EachNumericMap(self->VariableMap, DumpSymbolTable_entry);
}

void DeleteSymbolTable(SymbolTable * self) {
	DeleteNumericMap(self->VariableMap, DeleteSymbolTable_entry);
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