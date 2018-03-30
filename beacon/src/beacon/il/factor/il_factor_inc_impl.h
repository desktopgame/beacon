#pragma once
#ifndef BEACON_IL_IL_FACTOR_INC_H
#define BEACON_IL_IL_FACTOR_INC_H
#include "../il_operator_fixtype.h"
#include "../il_factor_interface.h"
#define IL_FACT2INC(fact) (il_factor_cast_inc(fact))
struct enviroment;

typedef struct il_factor_inc {
	il_factor* fact;
	fix_type type;
} il_factor_inc;

il_factor* il_factor_wrap_inc(il_factor_inc* self);

il_factor_inc* il_factor_inc_new(fix_type type);

void il_factor_inc_dump(il_factor_inc* self, int depth);

void il_factor_inc_generate(il_factor_inc* self, struct enviroment* env, il_load_cache* cache);

void il_factor_inc_load(il_factor_inc* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

generic_type* il_factor_inc_eval(il_factor_inc* self, struct enviroment* env, il_load_cache* cache);

void il_factor_inc_delete(il_factor_inc* self);

il_factor_inc* il_factor_cast_inc(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_INC_H
