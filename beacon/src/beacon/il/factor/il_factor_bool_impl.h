#pragma once
#ifndef BEACON_IL_IL_FACTOR_BOOL_H
#define BEACON_IL_IL_FACTOR_BOOL_H
#include <stdbool.h>
#include "../il_factor_interface.h"

struct enviroment;
struct type;
/**
 * boolリテラルを表す要素.
 */
typedef struct il_factor_bool {
	bool a;
} il_factor_bool;

il_factor* WrapILBool(il_factor_bool* self);

il_factor_bool* NewILBool(bool b);

void il_factor_bool_generate(il_factor_bool* self, struct enviroment* env, call_context* cctx);

generic_type* EvalILBool(il_factor_bool* self, struct enviroment* env, call_context* cctx);

char* ILBoolToString(il_factor_bool* self, struct enviroment* env);

void il_factor_bool_delete(il_factor_bool* self);

#endif // !SIGNAL_IL_IL_FACTOR_BOOL_H
