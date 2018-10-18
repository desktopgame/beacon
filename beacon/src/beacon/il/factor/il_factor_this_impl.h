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
typedef struct il_factor_this {
	generic_type* resolved;
} il_factor_this;

il_factor_this* NewILThis();

void GenerateILThis(il_factor_this* self, struct Enviroment* env, call_context* cctx);

void LoadILThis(il_factor_this* self, struct Enviroment* env, call_context* cctx);

generic_type* EvalILThis(il_factor_this* self, struct Enviroment* env, call_context* cctx);

char* ILThisToString(il_factor_this* self, struct Enviroment* env);

void DeleteILThis(il_factor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
