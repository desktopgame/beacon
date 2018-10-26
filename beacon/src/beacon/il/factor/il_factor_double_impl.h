#pragma once
#ifndef BEACON_IL_IL_FACTOR_DOUBLE_H
#define BEACON_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct il_factor_double {
	double value;
} il_factor_double;

il_factor* WrapILDouble(il_factor_double* self);

il_factor_double* NewILDouble(double d);

void GenerateILDouble(il_factor_double* self, Enviroment* env, CallContext* cctx);

void LoadILDouble(il_factor_double* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILDouble(il_factor_double* self, Enviroment* env, CallContext* cctx);

char* ILDoubleToString(il_factor_double* self, Enviroment* env);

void DeleteILDouble(il_factor_double* self);

#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
