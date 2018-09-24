#pragma once
#ifndef BEACON_IL_IL_FACTOR_STRING_H
#define BEACON_IL_IL_FACTOR_STRING_H
#include "../il_factor_interface.h"
#include "../../util/string_pool.h"

//struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct il_factor_string {
	string_view valuev;
} il_factor_string;

il_factor* il_factor_wrap_string(il_factor_string* self);

il_factor_string* il_factor_string_new(string_view valuev);

void il_factor_string_generate(il_factor_string* self, struct enviroment* env, call_context* cctx);

void il_factor_string_load(il_factor_string* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_string_eval(il_factor_string* self, struct enviroment* env, call_context* cctx);

char* il_factor_string_tostr(il_factor_string* self, struct enviroment* env);

void il_factor_string_delete(il_factor_string* self);

#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
