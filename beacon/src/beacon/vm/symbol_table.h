#pragma once
#ifndef BEACON_VM_SYMBOL_TABLE_H
#define BEACON_VM_SYMBOL_TABLE_H
#include "../util/tree_map.h"
#include "../util/numeric_map.h"
#include "../util/string_pool.h"
#include <stdio.h>
#include <stdbool.h>
//#include "../env/class.h"
struct generic_type;
struct symbol_entry;
/**
 * 変数名とインデックスの変換テーブルです.
 * オペコードの中では、添え字で変数アクセスを行います。
 */
typedef struct SymbolTable {
	NumericMap* VariableMap;
	int Count;
	int ScopeDepth;
} SymbolTable;

/**
 * シンボルテーブルを作成します.
 * @return
 */
SymbolTable* NewSymbolTable();

/**
 * 指定の名前に対応するインデックスを返します.
 * もしくは、既に登録されているならそれを返します。
 * @param self
 * @param gtp
 * @param namev
 * @return nameに対応するエントリが存在せず、clsがNULLならNULL
 */
struct symbol_entry* EntrySymbolTable(SymbolTable* self, struct generic_type* gtp, StringView namev);

/**
 * 既に指定の名前が含まれるなら true.
 * @param self
 * @param namev
 * @return
 */
bool IsContainsSymbol(SymbolTable* self, StringView namev);

/**
 * シンボルテーブルをダンプします.
 * @param self
 */
void DumpSymbolTable(SymbolTable* self);

/**
 * シンボルテーブルを開放します.
 * @param self
 */
void DeleteSymbolTable(SymbolTable* self);
#endif // !SIGNAL_VM_SYMBOL_TABLE_H
