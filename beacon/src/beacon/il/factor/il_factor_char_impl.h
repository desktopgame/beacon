#pragma once
#ifndef BEACON_IL_IL_FACTOR_CHAR_H
#define BEACON_IL_IL_FACTOR_CHAR_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 文字を表す要素.
 */
typedef struct ILFactor_char {
	char value;
} ILFactor_char;

ILFactor* WrapILChar(ILFactor_char* self);

ILFactor_char* NewILChar(char c);

void GenerateILChar(ILFactor_char* self, Enviroment* env, CallContext* cctx);

void LoadILChar(ILFactor_char* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILChar(ILFactor_char* self, Enviroment* env, CallContext* cctx);

char* ILCharToString(ILFactor_char* self, Enviroment* env);

void DeleteILChar(ILFactor_char* self);

#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
