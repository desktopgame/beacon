#pragma once
#ifndef BEACON_IL_IL_FACTOR_SUPER_H
#define BEACON_IL_IL_FACTOR_SUPER_H
#include "../il_context.h"
#include "../../env/generic_type.h"
struct enviroment;
struct type;

/**
 * superを表す要素.
 */

typedef struct il_factor_super {
	generic_type* resolved;
} il_factor_super;

il_factor_super* il_factor_super_new();

void il_factor_super_dump(il_factor_super* self, int depth);

void il_factor_super_generate(il_factor_super* self, struct enviroment* env, il_context* ilctx);

void il_factor_super_load(il_factor_super* self, struct enviroment* env, il_context* ilctx);

generic_type* il_factor_super_eval(il_factor_super* self, struct enviroment* env, il_context* ilctx);

char* il_factor_super_tostr(il_factor_super* self, struct enviroment* env, il_context* ilctx);

void il_factor_super_delete(il_factor_super* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
