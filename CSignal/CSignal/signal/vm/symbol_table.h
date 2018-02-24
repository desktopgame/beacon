#pragma once
#ifndef SIGNAL_VM_SYMBOL_TABLE_H
#define SIGNAL_VM_SYMBOL_TABLE_H
#include "../util/tree_map.h"
//#include "../env/class.h"
struct type;
struct symbol_entry;
/**
 * 変数名とインデックスの変換テーブルです.
 * オペコードの中では、添え字で変数アクセスを行います。
 */
typedef struct symbol_table {
	tree_map* map;
	int count;
} symbol_table;

/**
 * シンボルテーブルを作成します.
 * @return
 */
symbol_table* symbol_table_new();

/**
 * 指定の名前に対応するインデックスを返します.
 * もしくは、既に登録されているならそれを返します。
 * @param self
 * @param tp
 * @param name
 * @return nameに対応するエントリが存在せず、clsがNULLならNULL
 */
struct symbol_entry* symbol_table_entry(symbol_table* self, struct type* tp, const char* name);

/**
 * シンボルテーブルを開放します.
 * @param self
 */
void symbol_table_delete(symbol_table* self);
#endif // !SIGNAL_VM_SYMBOL_TABLE_H
