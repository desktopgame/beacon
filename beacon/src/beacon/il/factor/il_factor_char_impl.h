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

il_factor* WrapILChar(il_factor_char* self);

il_factor_char* NewILChar(char c);

void GenerateILChar(il_factor_char* self, Enviroment* env, CallContext* cctx);

void LoadILChar(il_factor_char* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILChar(il_factor_char* self, Enviroment* env, CallContext* cctx);

char* ILCharToString(il_factor_char* self, Enviroment* env);

void DeleteILChar(il_factor_char* self);

#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
