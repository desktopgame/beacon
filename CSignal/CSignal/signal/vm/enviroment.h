#pragma once
#ifndef SIGNAL_VM_ENVIROMENT_H
#define SIGNAL_VM_ENVIROMENT_H
#include "../util/vector.h"
#include "opcode_buf.h"
#include "symbol_table.h"
#include <stdbool.h>
struct class_;
struct object;
struct class_loader;
struct fqcn_cache;
/**
 * プログラムの実行環境です.
 * スタックや変数は実行時に変化しますが、
 * 定数プールやオペランドのようなコンパイル時に決定して
 * 不変なものをここでは enviroment と呼称します。
 */
typedef struct enviroment {
	struct class_loader* context_cll;
	opcode_buf* buf;
	symbol_table* sym_table;
	vector* constant_pool;
	//解析中の情報
	//FIXME:ここに持たせるべきじゃない
	vector* namespace_vec;
	vector* class_vec;
	bool toplevel;
//	struct class_* class_;
} enviroment;

/**
 * 環境を生成します.
 * @return
 */
enviroment* enviroment_new();

/**
 * 定数プールに整数を追加して、その位置を返します.
 * @param i
 * @return
 */
int enviroment_add_constant_int(enviroment* self, int i);

/**
 * 定数プールに浮動小数を追加して、その位置を返します.
 * @param d
 * @return
 */
int enviroment_add_constant_double(enviroment* self, double d);

/**
 * 定数プールに文字を追加して、その位置を返します.
 * @param c
 * @return
 */
int enviroment_add_constant_char(enviroment* self, char c);

/**
 * 定数プールに文字列を追加して、その位置を返します.
 * @param s
 * @return
 */
int enviroment_add_constant_string(enviroment* self, const char* s);

/**
 * 指定位置のオペコード/オペランドを返します.
 * @param self
 * @param index
 * @return
 */
vector_item enviroment_source_at(enviroment* self, int index);

/**
 * 指定位置の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* enviroment_constant_at(enviroment* self, int index);

/**
 * 指定位置の整数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* enviroment_constant_int_at(enviroment* self, int index);

/**
 * 指定位置の浮動小数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* enviroment_constant_double_at(enviroment* self, int index);

/**
 * 指定位置の文字型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* enviroment_constant_char_at(enviroment* self, int index);

/**
 * 指定位置の文字列型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* enviroment_constant_string_at(enviroment* self, int index);

/**
 * 現在のコンテキストでのクラスを返します.
 * @param self
 * @param fqcn
 * @return
 */
struct class_* enviroment_class(enviroment* self, struct fqcn_cache* fqcn);

/**
 * 環境を開放します.
 * @return
 */
void enviroment_delete(enviroment* self);
#endif // !SIGNAL_VM_ENVIROMENT_H
