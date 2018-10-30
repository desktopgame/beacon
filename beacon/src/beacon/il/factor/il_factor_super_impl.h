#pragma once
#ifndef BEACON_IL_IL_FACTOR_SUPER_H
#define BEACON_IL_IL_FACTOR_SUPER_H
#include "../../env/generic_type.h"
#include "../call_context.h"
struct Enviroment;
struct Type;

/**
 * superを表す要素.
 */

typedef struct ILSuper {
	GenericType* Resolved;
} ILSuper;

ILSuper* NewILSuper();

void GenerateILSuper(ILSuper* self, struct Enviroment* env, CallContext* cctx);

void LoadILSuper(ILSuper* self, struct Enviroment* env, CallContext* cctx);

GenericType* EvalILSuper(ILSuper* self, struct Enviroment* env, CallContext* cctx);

char* ILSuperToString(ILSuper* self, struct Enviroment* env);

void DeleteILSuper(ILSuper* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
