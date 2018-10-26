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

typedef struct il_factor_super {
	GenericType* resolved;
} il_factor_super;

il_factor_super* NewILSuper();

void GenerateILSuper(il_factor_super* self, struct Enviroment* env, CallContext* cctx);

void LoadILSuper(il_factor_super* self, struct Enviroment* env, CallContext* cctx);

GenericType* EvalILSuper(il_factor_super* self, struct Enviroment* env, CallContext* cctx);

char* ILSuperToString(il_factor_super* self, struct Enviroment* env);

void DeleteILSuper(il_factor_super* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
