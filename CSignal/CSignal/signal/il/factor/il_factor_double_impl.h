#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_DOUBLE_H
#define SIGNAL_IL_IL_FACTOR_DOUBLE_H
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct il_factor_double {
	double value;
} il_factor_double;

/**
 * 浮動小数リテラルを表す要素を作成します.
 * @param d
 * @return
 */
il_factor_double* il_factor_double_new(double d);

/**
 * 浮動小数リテラルを表す要素を開放します.
 * @param self
 */
void il_factor_double_delete(il_factor_double* self);
#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
