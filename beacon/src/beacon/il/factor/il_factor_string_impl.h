#pragma once
#ifndef BEACON_IL_IL_FACTOR_STRING_H
#define BEACON_IL_IL_FACTOR_STRING_H
#include "../il_factor_interface.h"
#define IL_FACT2STR(fact) (il_factor_cast_string(fact))
//struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct il_factor_string {
	char* value;
} il_factor_string;

il_factor* il_factor_wrap_string(il_factor_string* self);

il_factor_string* il_factor_string_new(const char* name);

void il_factor_string_dump(il_factor_string* self, int depth);

void il_factor_string_generate(il_factor_string* self, struct enviroment* env, il_context* ilctx);

void il_factor_string_load(il_factor_string* self, struct enviroment* env, il_context* ilctx);

generic_type* il_factor_string_eval(il_factor_string* self, struct enviroment* env, il_context* ilctx);

char* il_factor_string_tostr(il_factor_string* self, struct enviroment* env, il_context* ilctx);

void il_factor_string_delete(il_factor_string* self);

il_factor_string* il_factor_cast_string(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
