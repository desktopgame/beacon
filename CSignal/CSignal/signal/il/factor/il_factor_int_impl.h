#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_INT_H
#define SIGNAL_IL_IL_FACTOR_INT_H
#include <stdint.h>
/**
 * 整数リテラルを表す要素.
 */
typedef struct il_factor_int {
	int32_t value;
} il_factor_int;

/**
 * 整数リテラルを表す要素を作成します.
 * @param i
 * @return
 */
il_factor_int* il_factor_int_new(int32_t i);

/**
 * 整数リテラルを表す要素を開放します.
 * @param self
 */
void il_factor_int_delete(il_factor_int* self);
#endif // !SIGNAL_IL_IL_FACTOR_INT_H
