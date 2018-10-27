#pragma once
#ifndef BEACON_IL_IL_FACTOR_SUPER_H
#define BEACON_IL_IL_FACTOR_SUPER_H
#include "../../env/generic_type.h"
#include "../call_context.h"
struct Enviroment;
struct type;

/**
 * superを表す要素.
 */

typedef struct ILFactor_super {
	GenericType* resolved;
} ILFactor_super;

ILFactor_super* NewILSuper();

void GenerateILSuper(ILFactor_super* self, struct Enviroment* env, CallContext* cctx);

void LoadILSuper(ILFactor_super* self, struct Enviroment* env, CallContext* cctx);

GenericType* EvalILSuper(ILFactor_super* self, struct Enviroment* env, CallContext* cctx);

char* ILSuperToString(ILFactor_super* self, struct Enviroment* env);

void DeleteILSuper(ILFactor_super* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
