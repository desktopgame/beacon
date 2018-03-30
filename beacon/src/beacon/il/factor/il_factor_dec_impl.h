#pragma once
#ifndef BEACON_IL_IL_FACTOR_DEC_H
#define BEACON_IL_IL_FACTOR_DEC_H
#include "../il_operator_fixtype.h"
#include "../il_factor_interface.h"

#define IL_FACT2DEC(fact) (il_factor_cast_dec(fact))

typedef struct il_factor_dec {
	il_factor* fact;
	fix_type type;
} il_factor_dec;

il_factor* il_factor_wrap_dec(il_factor_dec* self);

il_factor_dec* il_factor_dec_new(fix_type type);

void il_factor_dec_dump(il_factor_dec* self, int depth);

void il_factor_dec_generate(il_factor_dec* self, struct enviroment* env, il_load_cache* cache);

void il_factor_dec_load(il_factor_dec* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

generic_type* il_factor_dec_eval(il_factor_dec* self, struct enviroment* env, il_load_cache* cache);

void il_factor_dec_delete(il_factor_dec* self);

il_factor_dec* il_factor_cast_dec(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_DEC_H
