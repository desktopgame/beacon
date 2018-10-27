#pragma once
#ifndef BEACON_IL_IL_FACTOR_CHAR_H
#define BEACON_IL_IL_FACTOR_CHAR_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 文字を表す要素.
 */
typedef struct ILChar {
	char Value;
} ILChar;

ILFactor* WrapILChar(ILChar* self);

ILChar* NewILChar(char c);

void GenerateILChar(ILChar* self, Enviroment* env, CallContext* cctx);

void LoadILChar(ILChar* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILChar(ILChar* self, Enviroment* env, CallContext* cctx);

char* ILCharToString(ILChar* self, Enviroment* env);

void DeleteILChar(ILChar* self);

#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
