#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct Enviroment;
struct GenericType;

typedef struct il_factor_variable_static {
	FQCNCache* fqcn;
	Vector* type_args;
} il_factor_variable_static;

il_factor_variable_static* NewILVariableStatic();

void GenerateILVariableStatic(il_factor_variable_static* self, Enviroment* env, CallContext* cctx);

void LoadILVariableStatic(il_factor_variable_static * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableStatic(il_factor_variable_static * self, Enviroment * env, CallContext* cctx);

char* ILVariableStaticToString(il_factor_variable_static * self, Enviroment * env);

void DeleteILVariableStatic(il_factor_variable_static* self);
#endif