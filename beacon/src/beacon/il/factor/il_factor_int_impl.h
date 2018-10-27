#pragma once
#ifndef BEACON_IL_IL_FACTOR_INT_H
#define BEACON_IL_IL_FACTOR_INT_H
#include "../il_factor_interface.h"
#include <stdint.h>
//struct opcode_buf;

/**
 * 整数リテラルを表す要素.
 */
typedef struct ILFactor_int {
	int32_t value;
	int count;
} ILFactor_int;

ILFactor* WrapILInt(ILFactor_int* self);

#define ILFactor_int_new(i) (MallocILInt(i, __FILE__, __LINE__))
ILFactor_int* MallocILInt(int32_t i, const char* filename, int lineno);

void GenerateILInt(ILFactor_int* self, Enviroment* env, CallContext* cctx);

void LoadILInt(ILFactor_int* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILInt(ILFactor_int* self, Enviroment* env, CallContext* cctx);

char* ILIntToString(ILFactor_int* self, Enviroment* env);

void DeleteILInt(ILFactor_int* self);

#endif // !SIGNAL_IL_IL_FACTOR_INT_H
