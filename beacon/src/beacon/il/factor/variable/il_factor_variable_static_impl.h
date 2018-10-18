#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct Enviroment;
struct generic_type;

typedef struct il_factor_variable_static {
	fqcn_cache* fqcn;
	Vector* type_args;
} il_factor_variable_static;

il_factor_variable_static* NewILVariableStatic();

void GenerateILVariableStatic(il_factor_variable_static* self, Enviroment* env, call_context* cctx);

void LoadILVariableStatic(il_factor_variable_static * self, Enviroment * env, call_context* cctx);

struct generic_type* EvalILVariableStatic(il_factor_variable_static * self, Enviroment * env, call_context* cctx);

char* ILVariableStaticToString(il_factor_variable_static * self, Enviroment * env);

void DeleteILVariableStatic(il_factor_variable_static* self);
#endif