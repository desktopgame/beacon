#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct enviroment;
struct generic_type;

typedef struct il_factor_variable_static {
	fqcn_cache* fqcn;
	vector* type_args;
} il_factor_variable_static;

il_factor_variable_static* il_factor_variable_static_new();

void il_factor_variable_static_generate(il_factor_variable_static* self, struct enviroment* env);

void il_factor_variable_static_load(il_factor_variable_static * self, struct enviroment * env);

struct generic_type* il_factor_variable_static_eval(il_factor_variable_static * self, struct enviroment * env);

char* il_factor_variable_static_tostr(il_factor_variable_static * self, struct enviroment * env);

void il_factor_variable_static_delete(il_factor_variable_static* self);
#endif