#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
struct enviroment;
struct generic_type;

typedef struct il_factor_invoke_static {
	fqcn_cache* fqcn;
	vector* args;
	vector* type_args;
} il_factor_invoke_static;

il_factor_invoke_static* il_factor_invoke_static_new();

void il_factor_invoke_static_generate(il_factor_invoke_static* self, struct enviroment* env, il_load_cache* cache);

void il_factor_invoke_static_load(il_factor_invoke_static * self, struct enviroment * env, il_load_cache* cache, il_ehandler* eh);

struct generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, struct enviroment * env, il_load_cache* cache);

void il_factor_invoke_static_delete(il_factor_invoke_static* self);
#endif