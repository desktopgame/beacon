#pragma once
#ifndef BEACON_IL_IL_FACTOR_CAST_H
#define BEACON_IL_IL_FACTOR_CAST_H
#include "../il_factor_interface.h"

#define IL_FACT2CAST(fact) (il_factor_cast_cast(fact))

struct generic_cache;
struct type;
struct enviroment;

/**
 * キャストを表す構造体.
 */
typedef struct il_factor_cast {
	struct generic_cache* fqcn;
	il_factor* fact;
} il_factor_cast;

il_factor* il_factor_wrap_cast(il_factor_cast* self);

il_factor_cast* il_factor_cast_new(il_factor* fact);

void il_factor_cast_dump(il_factor_cast* self, int depth);

void il_factor_cast_generate(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

void il_factor_cast_load(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

generic_type* il_factor_cast_eval(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

char* il_factor_cast_tostr(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

void il_factor_cast_delete(il_factor_cast* self);

il_factor_cast* il_factor_cast_cast(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_CAST_H
