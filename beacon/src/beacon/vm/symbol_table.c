#include "symbol_table.h"
#include "../env/TYPE_IMPL.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
#include "symbol_entry.h"
//#include "../env/generic_type.h"
#include <assert.h>
#include <string.h>
#include "../env/generic_type.h"
#include "../util/text.h"

// proto
static void delete_entry(bc_NumericMapKey key, bc_NumericMapItem item);
static void dump_entry(bc_NumericMapKey key, bc_NumericMapItem item);

bc_SymbolTable* bc_NewSymbolTable() {
        bc_SymbolTable* ret =
            (bc_SymbolTable*)MEM_MALLOC(sizeof(bc_SymbolTable));
        ret->Count = 1;
        ret->VariableMap = bc_NewNumericMap();
        ret->ScopeDepth = 0;
        return ret;
}

bc_SymbolEntry* bc_EntrySymbolTable(bc_SymbolTable* self, bc_GenericType* gtp,
                                    bc_StringView namev) {
        bc_NumericMap* data = bc_GetNumericMapCell(self->VariableMap, namev);
        if (data) {
                return ((bc_SymbolEntry*)data->Item);
        }
        //フィールドアクセスのために追加
        if (gtp == NULL) {
                return NULL;
        }
        int ret = self->Count;
        bc_SymbolEntry* e = bc_NewSymbolEntry();
        e->Index = self->Count;
        e->GType = gtp;
        e->ScopeDepth = self->ScopeDepth;
        bc_PutNumericMap(self->VariableMap, namev, e);
        self->Count++;
        return e;
}

bool bc_IsContainsSymbol(bc_SymbolTable* self, bc_StringView namev) {
        return bc_GetNumericMapCell(self->VariableMap, namev) != NULL;
}

void bc_DumpSymbolTable(bc_SymbolTable* self) {
        bc_EachNumericMap(self->VariableMap, dump_entry);
}

void bc_DeleteSymbolTable(bc_SymbolTable* self) {
        bc_DeleteNumericMap(self->VariableMap, delete_entry);
        MEM_FREE(self);
}

// private
static void delete_entry(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_SymbolEntry* e = (bc_SymbolEntry*)item;
        bc_DeleteSymbolEntry(e);
}
static void dump_entry(bc_NumericMapKey key, bc_NumericMapItem item) {
        printf("[%s] = %d\n", bc_Ref2Str(key), ((bc_SymbolEntry*)item)->Index);
}