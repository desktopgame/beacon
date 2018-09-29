#pragma once
#ifndef BEACON_VM_ENVIROMENT_H
#define BEACON_VM_ENVIROMENT_H
#include "../util/vector.h"
#include "../util/string_pool.h"
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
	struct class_loader* context_ref;
	opcode_buf* buf;
	symbol_table* sym_table;
	Vector* constant_pool_vec;
	Vector* line_range_vec;
} enviroment;

/**
 * 環境を生成します.
 * @return
 */
enviroment* NewEnviroment();

/**
 * 指定の行番号を開始します.
 * @param self
 * @param lineno
 */
void AddRangeEnviroment(enviroment* self, int lineno);

/**
 * この enviroment に含まれるオペコードの一覧をダンプします.
 * DumpOpcodeBuf との違いは、行番号を出力できる点です。
 * @param self
 * @param depth
 */
void DumpEnviromentOp(enviroment* self, int depth);

/**
 * 定数プールに整数を追加して、その位置を返します.
 * @param i
 * @return
 */
int AddCIntEnviroment(enviroment* self, int i);

/**
 * 定数プールに浮動小数を追加して、その位置を返します.
 * @param d
 * @return
 */
int AddCDoubleEnviroment(enviroment* self, double d);

/**
 * 定数プールに文字を追加して、その位置を返します.
 * @param c
 * @return
 */
int AddCCharEnviroment(enviroment* self, char c);

/**
 * 定数プールに文字列を追加して、その位置を返します.
 * @param sv
 * @return
 */
int AddCStringEnviroment(enviroment* self, string_view sv);

/**
 * 指定位置のオペコード/オペランドを返します.
 * @param self
 * @param index
 * @return
 */
VectorItem GetEnviromentSourceAt(enviroment* self, int index);

/**
 * 指定位置の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* GetEnviromentConstantAt(enviroment* self, int index);

/**
 * 指定位置の整数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* GetEnviromentCIntAt(enviroment* self, int index);

/**
 * 指定位置の浮動小数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* GetEnviromentCDoubleAt(enviroment* self, int index);

/**
 * 指定位置の文字型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* GetEnviromentCCharAt(enviroment* self, int index);

/**
 * 指定位置の文字列型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct object* GetEnviromentCStringAt(enviroment* self, int index);

/**
 * 環境を開放します.
 * @return
 */
void DeleteEnviroment(enviroment* self);
#endif // !SIGNAL_VM_ENVIROMENT_H
