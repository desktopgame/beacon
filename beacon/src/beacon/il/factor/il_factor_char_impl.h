#pragma once
#ifndef BEACON_IL_IL_FACTOR_CHAR_H
#define BEACON_IL_IL_FACTOR_CHAR_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 文字を表す要素.
 */
typedef struct il_factor_char {
	char value;
} il_factor_char;

il_factor* il_factor_wrap_char(il_factor_char* self);

il_factor_char* il_factor_char_new(char c);

void il_factor_char_generate(il_factor_char* self, struct enviroment* env, call_context* cctx);

void il_factor_char_load(il_factor_char* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_char_eval(il_factor_char* self, struct enviroment* env, call_context* cctx);

char* il_factor_char_tostr(il_factor_char* self, struct enviroment* env);

void il_factor_char_delete(il_factor_char* self);

#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
