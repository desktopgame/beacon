#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../../env/generic_type.h"
#include "../call_context.h"
struct Enviroment;
struct type;
/**
 * thisを表す要素.
 */
typedef struct ILFactor_this {
	GenericType* resolved;
} ILFactor_this;

ILFactor_this* NewILThis();

void GenerateILThis(ILFactor_this* self, struct Enviroment* env, CallContext* cctx);

void LoadILThis(ILFactor_this* self, struct Enviroment* env, CallContext* cctx);

GenericType* EvalILThis(ILFactor_this* self, struct Enviroment* env, CallContext* cctx);

char* ILThisToString(ILFactor_this* self, struct Enviroment* env);

void DeleteILThis(ILFactor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
