#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct Enviroment;
struct GenericType;

typedef struct ILFactor_variable_static {
	FQCNCache* fqcn;
	Vector* type_args;
} ILFactor_variable_static;

ILFactor_variable_static* NewILVariableStatic();

void GenerateILVariableStatic(ILFactor_variable_static* self, Enviroment* env, CallContext* cctx);

void LoadILVariableStatic(ILFactor_variable_static * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableStatic(ILFactor_variable_static * self, Enviroment * env, CallContext* cctx);

char* ILVariableStaticToString(ILFactor_variable_static * self, Enviroment * env);

void DeleteILVariableStatic(ILFactor_variable_static* self);
#endif