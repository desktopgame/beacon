#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../../env/generic_type.h"
#include "../call_context.h"
struct Enviroment;
struct Type;
/**
 * thisを表す要素.
 */
typedef struct ILThis {
	GenericType* Resolved;
} ILThis;

ILThis* NewILThis();

void GenerateILThis(ILThis* self, struct Enviroment* env, CallContext* cctx);

void LoadILThis(ILThis* self, struct Enviroment* env, CallContext* cctx);

GenericType* EvalILThis(ILThis* self, struct Enviroment* env, CallContext* cctx);

char* ILThisToString(ILThis* self, struct Enviroment* env);

void DeleteILThis(ILThis* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
