#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct Enviroment;
struct GenericType;

typedef struct ILVariable_static {
	FQCNCache* fqcn;
	Vector* type_args;
} ILVariable_static;

ILVariable_static* NewILVariableStatic();

void GenerateILVariableStatic(ILVariable_static* self, Enviroment* env, CallContext* cctx);

void LoadILVariableStatic(ILVariable_static * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableStatic(ILVariable_static * self, Enviroment * env, CallContext* cctx);

char* ILVariableStaticToString(ILVariable_static * self, Enviroment * env);

void DeleteILVariableStatic(ILVariable_static* self);
#endif