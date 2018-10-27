#pragma once
#ifndef BEACON_IL_IL_FACTOR_DOUBLE_H
#define BEACON_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"

//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct ILDouble {
	double Value;
} ILDouble;

ILFactor* WrapILDouble(ILDouble* self);

ILDouble* NewILDouble(double d);

void GenerateILDouble(ILDouble* self, Enviroment* env, CallContext* cctx);

void LoadILDouble(ILDouble* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILDouble(ILDouble* self, Enviroment* env, CallContext* cctx);

char* ILDoubleToString(ILDouble* self, Enviroment* env);

void DeleteILDouble(ILDouble* self);

#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
