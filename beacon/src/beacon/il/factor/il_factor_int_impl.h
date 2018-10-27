#pragma once
#ifndef BEACON_IL_IL_FACTOR_INT_H
#define BEACON_IL_IL_FACTOR_INT_H
#include "../il_factor_interface.h"
#include <stdint.h>
//struct opcode_buf;

/**
 * 整数リテラルを表す要素.
 */
typedef struct ILInt {
	int32_t Value;
	int Count;
} ILInt;

ILFactor* WrapILInt(ILInt* self);

#define ILInt_new(i) (MallocILInt(i, __FILE__, __LINE__))
ILInt* MallocILInt(int32_t i, const char* filename, int lineno);

void GenerateILInt(ILInt* self, Enviroment* env, CallContext* cctx);

void LoadILInt(ILInt* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILInt(ILInt* self, Enviroment* env, CallContext* cctx);

char* ILIntToString(ILInt* self, Enviroment* env);

void DeleteILInt(ILInt* self);

#endif // !SIGNAL_IL_IL_FACTOR_INT_H
