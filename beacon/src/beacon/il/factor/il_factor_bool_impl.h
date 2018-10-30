#pragma once
#ifndef BEACON_IL_IL_FACTOR_BOOL_H
#define BEACON_IL_IL_FACTOR_BOOL_H
#include <stdbool.h>
#include "../il_factor_interface.h"

struct Enviroment;
struct Type;
/**
 * boolリテラルを表す要素.
 */
typedef struct ILBool {
	bool Value;
} ILBool;

ILFactor* WrapILBool(ILBool* self);

ILBool* NewILBool(bool b);

void GenerateILBool(ILBool* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILBool(ILBool* self, Enviroment* env, CallContext* cctx);

char* ILBoolToString(ILBool* self, Enviroment* env);

void DeleteILBool(ILBool* self);

#endif // !SIGNAL_IL_IL_FACTOR_BOOL_H
