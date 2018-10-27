#pragma once
#ifndef BEACON_IL_IL_FACTOR_STRING_H
#define BEACON_IL_IL_FACTOR_STRING_H
#include "../il_factor_interface.h"
#include "../../util/string_pool.h"

//struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct ILString {
	StringView Value;
} ILString;

ILFactor* WrapILString(ILString* self);

ILString* NewILString(StringView valuev);

void GenerateILString(ILString* self, Enviroment* env, CallContext* cctx);

void LoadILString(ILString* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILString(ILString* self, Enviroment* env, CallContext* cctx);

char* ILStringToString(ILString* self, Enviroment* env);

void DeleteILString(ILString* self);

#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
