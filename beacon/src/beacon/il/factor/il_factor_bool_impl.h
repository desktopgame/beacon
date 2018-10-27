#pragma once
#ifndef BEACON_IL_IL_FACTOR_BOOL_H
#define BEACON_IL_IL_FACTOR_BOOL_H
#include <stdbool.h>
#include "../il_factor_interface.h"

struct Enviroment;
struct type;
/**
 * boolリテラルを表す要素.
 */
typedef struct ILFactor_bool {
	bool a;
} ILFactor_bool;

ILFactor* WrapILBool(ILFactor_bool* self);

ILFactor_bool* NewILBool(bool b);

void GenerateILBool(ILFactor_bool* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILBool(ILFactor_bool* self, Enviroment* env, CallContext* cctx);

char* ILBoolToString(ILFactor_bool* self, Enviroment* env);

void DeleteILBool(ILFactor_bool* self);

#endif // !SIGNAL_IL_IL_FACTOR_BOOL_H
