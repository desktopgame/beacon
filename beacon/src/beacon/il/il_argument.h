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
il_argument* NewILArgument();

/**
 * 実引数を表す要素を開放します.
 * @param self
 */
void DeleteILArgument(il_argument* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_H
