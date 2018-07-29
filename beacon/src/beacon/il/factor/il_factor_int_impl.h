#pragma once
#ifndef BEACON_IL_IL_FACTOR_INT_H
#define BEACON_IL_IL_FACTOR_INT_H
#include "../il_factor_interface.h"
#include <stdint.h>
//struct opcode_buf;
#define IL_FACT2INT(fact) (il_factor_cast_int(fact))
/**
 * 整数リテラルを表す要素.
 */
typedef struct il_factor_int {
	int32_t value;
	int count;
} il_factor_int;

il_factor* il_factor_wrap_int(il_factor_int* self);

#define il_factor_int_new(i) (il_factor_int_malloc(i, __FILE__, __LINE__))
il_factor_int* il_factor_int_malloc(int32_t i, const char* filename, int lineno);

void il_factor_int_dump(il_factor_int* self, int depth);

void il_factor_int_generate(il_factor_int* self, struct enviroment* env, call_context* cctx);

void il_factor_int_load(il_factor_int* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_int_eval(il_factor_int* self, struct enviroment* env, call_context* cctx);

char* il_factor_int_tostr(il_factor_int* self, struct enviroment* env);

void il_factor_int_delete(il_factor_int* self);

il_factor_int* il_factor_cast_int(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_INT_H
