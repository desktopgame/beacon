#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
struct enviroment;
struct generic_type;

typedef struct il_factor_invoke {
	il_factor* receiver;
	vector* args;
	vector* type_args;
} il_factor_invoke;

il_factor_invoke* il_factor_invoke_new();

void il_factor_invoke_generate(il_factor_invoke* self, struct enviroment* env, il_load_cache* cache);

void il_factor_invoke_load(il_factor_invoke * self, struct enviroment * env, il_load_cache* cache, il_ehandler* eh);

struct generic_type* il_factor_invoke_eval(il_factor_invoke * self, struct enviroment * env, il_load_cache* cache);

void il_factor_invoke_delete(il_factor_invoke* self);
#endif