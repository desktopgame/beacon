#pragma once
#ifndef BEACON_IL_IL_FACTOR_STRING_H
#define BEACON_IL_IL_FACTOR_STRING_H
#include "../il_factor_interface.h"
#include "../../util/string_pool.h"

//struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct ILFactor_string {
	StringView valuev;
} ILFactor_string;

ILFactor* WrapILString(ILFactor_string* self);

ILFactor_string* NewILString(StringView valuev);

void GenerateILString(ILFactor_string* self, Enviroment* env, CallContext* cctx);

void LoadILString(ILFactor_string* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILString(ILFactor_string* self, Enviroment* env, CallContext* cctx);

char* ILStringToString(ILFactor_string* self, Enviroment* env);

void DeleteILString(ILFactor_string* self);

#endif // !SIGNAL_IL_IL_FACTOR_STRING_H
