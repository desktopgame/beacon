#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_AS_H
#define SIGNAL_IL_IL_FACTOR_AS_H
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"

typedef struct il_factor_as {
	il_factor* fact;
	generic_cache* fqcn;
} il_factor_as;

struct enviroment;
struct type;
struct field;

il_factor* il_factor_wrap_as(il_factor_as* self);

il_factor_as* il_factor_as_new();

void il_factor_as_dump(il_factor_as* self, int depth);

void il_factor_as_generate(il_factor_as* self, struct enviroment* env, il_load_cache* cache);

void il_factor_as_load(il_factor_as* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

struct type* il_factor_as_eval(il_factor_as* self, struct enviroment* env, il_load_cache* cache);

void il_factor_as_delete(il_factor_as* self);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
