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
	StringView valuev;
} il_factor_string;

il_factor* WrapILString(il_factor_string* self);

il_factor_string* NewILString(StringView valuev);

void GenerateILString(il_factor_string* self, Enviroment* env, CallContext* cctx);

void LoadILString(il_factor_string* self, Enviroment* env, CallContext* cctx);

generic_type* EvalILString(il_factor_string* self, Enviroment* env, CallContext* cctx);

char* ILStringToString(il_factor_string* self, Enviroment* env);

void DeleteILString(il_factor_string* self);

#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
