#pragma once
#ifndef BEACON_IL_IL_FACTOR_DOUBLE_H
#define BEACON_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"
#define IL_FACT2DOUBLE(fact) (il_factor_cast_double_T(fact))
//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct il_factor_double {
	double value;
} il_factor_double;

il_factor* il_factor_wrap_double(il_factor_double* self);

il_factor_double* il_factor_double_new(double d);

void il_factor_double_dump(il_factor_double* self, int depth);

void il_factor_double_generate(il_factor_double* self, struct enviroment* env, call_context* cctx);

void il_factor_double_load(il_factor_double* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_double_eval(il_factor_double* self, struct enviroment* env, call_context* cctx);

char* il_factor_double_tostr(il_factor_double* self, struct enviroment* env);

void il_factor_double_delete(il_factor_double* self);

il_factor_double* il_factor_cast_double_T(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
