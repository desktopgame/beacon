#pragma once
#ifndef BEACON_IL_IL_ARGUMENT_H
#define BEACON_IL_IL_ARGUMENT_H
#include "il_factor_interface.h"
/**
 * 実引数を表す要素.
 */
typedef struct il_argument {
	//char* name;
	il_factor* factor;
} il_argument;

/**
 * 実引数を表す要素を作成します.
 * @return
 */
il_argument* il_argument_new();

/**
 * 実引数を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_argument_dump(il_argument* self, int depth);

/**
 * 実引数を表す要素を開放します.
 * @param self
 */
void il_argument_delete(il_argument* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_H
