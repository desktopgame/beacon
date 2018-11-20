//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file symbol_entry.h
 * @brief ローカル変数を表す構造体を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_VM_SYMBOL_ENTRY_H
#define BEACON_VM_SYMBOL_ENTRY_H
//#include "../env/class.h"
#include "../util/string_pool.h"
struct bc_GenericType;
/**
 * シンボルを表す構造体.
 */
typedef struct bc_SymbolEntry {
	int Index;
	int ScopeDepth;
	struct bc_GenericType* GType;
} bc_SymbolEntry;

/**
 * エントリを作成します.
 * @return
 */
bc_SymbolEntry* bc_NewSymbolEntry();

/**
 * エントリを開放します.
 * @param self
 */
void bc_DeleteSymbolEntry(bc_SymbolEntry* self);
#endif // !SIGNAL_VM_SYMBOL_ENTRY_H
