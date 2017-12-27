#pragma once
#ifndef SIGNAL_VM_ENVIROMENT_H
#define SIGNAL_VM_ENVIROMENT_H
#include "../util/vector.h"
#include "opcode_buf.h"
struct class_;
/**
 * プログラムの実行環境です.
 * スタックや変数は実行時に変化しますが、
 * 定数プールやオペランドのようなコンパイル時に決定して
 * 不変なものをここでは enviroment と呼称します。
 */
typedef struct enviroment {
	opcode_buf* buf;
	vector* constant_pool;
	struct class_* class_;
} enviroment;

/**
 * 環境を生成します.
 * @return
 */
enviroment* enviroment_new();

/**
 * 定数プールに値を追加して、その位置を返します.
 * @param item
 * @return
 */
int enviroment_add_constant(enviroment* self, vector_item item);

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
vector_item enviroment_constant_at(enviroment* self, int index);

/**
 * 環境を開放します.
 * @return
 */
void enviroment_delete(enviroment* self);
#endif // !SIGNAL_VM_ENVIROMENT_H
