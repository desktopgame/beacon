#pragma once
#ifndef BEACON_IL_IL_FACTOR_DOUBLE_H
#define BEACON_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct ILFactor_double {
	double value;
} ILFactor_double;

ILFactor* WrapILDouble(ILFactor_double* self);

ILFactor_double* NewILDouble(double d);

void GenerateILDouble(ILFactor_double* self, Enviroment* env, CallContext* cctx);

void LoadILDouble(ILFactor_double* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILDouble(ILFactor_double* self, Enviroment* env, CallContext* cctx);

char* ILDoubleToString(ILFactor_double* self, Enviroment* env);

void DeleteILDouble(ILFactor_double* self);

#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
