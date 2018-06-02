#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../../env/generic_type.h"
struct enviroment;
struct type;
/**
 * thisを表す要素.
 */
typedef struct il_factor_this {
	generic_type* resolved;
} il_factor_this;

il_factor_this* il_factor_this_new();

void il_factor_this_dump(il_factor_this* self, int depth);

void il_factor_this_generate(il_factor_this* self, struct enviroment* env);

void il_factor_this_load(il_factor_this* self, struct enviroment* env);

generic_type* il_factor_this_eval(il_factor_this* self, struct enviroment* env);

char* il_factor_this_tostr(il_factor_this* self, struct enviroment* env);

void il_factor_this_delete(il_factor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
