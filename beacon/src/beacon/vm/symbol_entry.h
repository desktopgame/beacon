#pragma once
#ifndef BEACON_VM_SYMBOL_ENTRY_H
#define BEACON_VM_SYMBOL_ENTRY_H
//#include "../env/class.h"
#include "../util/string_pool.h"
struct generic_type;
/**
 * シンボルを表す構造体.
 */
typedef struct symbol_entry {
	int index;
	int scope_depth;
	struct generic_type* gtype;
} symbol_entry;

/**
 * エントリを作成します.
 * @return
 */
symbol_entry* NewSymbolEntry();

/**
 * エントリを開放します.
 * @param self
 */
void DeleteSymbolEntry(symbol_entry* self);
#endif // !SIGNAL_VM_SYMBOL_ENTRY_H
