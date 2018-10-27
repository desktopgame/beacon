#pragma once
#ifndef BEACON_IL_IL_ARGUMENT_H
#define BEACON_IL_IL_ARGUMENT_H
#include "il_factor_interface.h"
/**
 * 実引数を表す要素.
 */
typedef struct ILArgument {
	//char* name;
	ILFactor* Factor;
} ILArgument;

/**
 * 実引数を表す要素を作成します.
 * @return
 */
ILArgument* NewILArgument();

/**
 * 実引数を表す要素を開放します.
 * @param self
 */
void DeleteILArgument(ILArgument* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_H
