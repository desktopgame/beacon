#pragma once
#ifndef BEACON_VM_SYMBOL_ENTRY_H
#define BEACON_VM_SYMBOL_ENTRY_H
//#include "../env/class.h"
#include "../util/string_pool.h"
struct GenericType;
/**
 * シンボルを表す構造体.
 */
typedef struct SymbolEntry {
	int Index;
	int ScopeDepth;
	struct GenericType* GType;
} SymbolEntry;

/**
 * エントリを作成します.
 * @return
 */
SymbolEntry* NewSymbolEntry();

/**
 * エントリを開放します.
 * @param self
 */
void DeleteSymbolEntry(SymbolEntry* self);
#endif // !SIGNAL_VM_SYMBOL_ENTRY_H
