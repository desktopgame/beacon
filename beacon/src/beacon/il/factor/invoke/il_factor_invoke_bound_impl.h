#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
struct enviroment;
struct generic_type;
struct method;
//binded? bound?

typedef struct il_factor_invoke_bound {
	char* name;
	vector* type_args;
	vector* args;
	struct method* m;
	int index;
	struct generic_type* resolved;
} il_factor_invoke_bound;

il_factor_invoke_bound* il_factor_invoke_bound_new(const char* name);

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, struct enviroment* env, il_context* ilctx);

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, struct enviroment * env, il_context* ilctx);

struct generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, struct enviroment * env, il_context* ilctx);

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self);
#endif