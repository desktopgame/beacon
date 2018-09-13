#pragma once
#ifndef BEACON_IL_IL_FACTOR_AS_H
#define BEACON_IL_IL_FACTOR_AS_H
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"

typedef enum cast_mode {
	cast_down_T,
	cast_up_T,
	cast_unknown_T,
} cast_mode;

/**
 * as演算子を表す構造体.
 */
typedef struct il_factor_as {
	il_factor* fact;
	generic_cache* fqcn;
	generic_type* gtype;
	cast_mode mode;
} il_factor_as;

struct enviroment;
struct type;
struct field;

il_factor* il_factor_wrap_as(il_factor_as* self);

il_factor_as* il_factor_as_new();

void il_factor_as_dump(il_factor_as* self, int depth);

void il_factor_as_generate(il_factor_as* self, struct enviroment* env, call_context* cctx);

void il_factor_as_load(il_factor_as* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_as_eval(il_factor_as* self, struct enviroment* env, call_context* cctx);

void il_factor_as_delete(il_factor_as* self);

char* il_factor_as_tostr(il_factor_as* self, enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
