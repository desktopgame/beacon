#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct Enviroment;
struct GenericType;

typedef struct ILVariableStatic {
	FQCNCache* FQCN;
	Vector* TypeArgs;
} ILVariableStatic;

ILVariableStatic* NewILVariableStatic();

void GenerateILVariableStatic(ILVariableStatic* self, Enviroment* env, CallContext* cctx);

void LoadILVariableStatic(ILVariableStatic * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableStatic(ILVariableStatic * self, Enviroment * env, CallContext* cctx);

char* ILVariableStaticToString(ILVariableStatic * self, Enviroment * env);

void DeleteILVariableStatic(ILVariableStatic* self);
#endif