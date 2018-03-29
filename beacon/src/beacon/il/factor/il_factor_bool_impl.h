#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_BOOL_H
#define SIGNAL_IL_IL_FACTOR_BOOL_H
#include <stdbool.h>
#include "../il_factor_interface.h"

struct enviroment;
struct type;

typedef struct il_factor_bool {
	bool a;
} il_factor_bool;

il_factor* il_factor_wrap_bool(il_factor_bool* self);

il_factor_bool* il_factor_bool_new(bool b);

void il_factor_bool_dump(il_factor_bool* self, int depth);

void il_factor_bool_generate(il_factor_bool* self, struct enviroment* env, il_load_cache* cache);

generic_type* il_factor_bool_eval(il_factor_bool* self, struct enviroment* env, il_load_cache* cache);

void il_factor_bool_delete(il_factor_bool* self);
#endif // !SIGNAL_IL_IL_FACTOR_BOOL_H