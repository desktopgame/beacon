#pragma once
#ifndef BEACON_IL_IL_FACTOR_INT_H
#define BEACON_IL_IL_FACTOR_INT_H
#include "../il_factor_interface.h"
#include <stdint.h>
//struct opcode_buf;

/**
 * 整数リテラルを表す要素.
 */
typedef struct il_factor_int {
	int32_t value;
	int count;
} il_factor_int;

il_factor* WrapILInt(il_factor_int* self);

#define il_factor_int_new(i) (MallocILInt(i, __FILE__, __LINE__))
il_factor_int* MallocILInt(int32_t i, const char* filename, int lineno);

void GenerateILInt(il_factor_int* self, Enviroment* env, CallContext* cctx);

void LoadILInt(il_factor_int* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILInt(il_factor_int* self, Enviroment* env, CallContext* cctx);

char* ILIntToString(il_factor_int* self, Enviroment* env);

void DeleteILInt(il_factor_int* self);

#endif // !SIGNAL_IL_IL_FACTOR_INT_H
