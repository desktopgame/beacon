#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_VARIABLE_H
#define SIGNAL_IL_IL_FACTOR_VARIABLE_H
#include "../il_factor_interface.h"
/**
 * 変数を表す要素.
 */
typedef struct il_factor_variable {
	char* name;
} il_factor_variable;

/**
 * 変数をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_variable(il_factor_variable* self);

/**
 * 変数を作成します.
 * @param name
 * @return
 */
il_factor_variable* il_factor_variable_new(const char* name);

/**
 * 変数を出力します.
 * @param self
 * @param depth
 */
void il_factor_variable_dump(il_factor_variable* self, int depth);

/**
 * 変数を開放します.
 */
void il_factor_variable_delete(il_factor_variable* self);
#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
