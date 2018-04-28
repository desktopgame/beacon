#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
struct enviroment;
struct generic_type;
struct method;

typedef struct il_factor_invoke_static {
	char* name;
	fqcn_cache* fqcn;
	vector* args;
	vector* type_args;
	struct method* m;
	int index;
	struct generic_type* resolved;
} il_factor_invoke_static;

il_factor_invoke_static* il_factor_invoke_static_new(const char* name);

void il_factor_invoke_static_dump(il_factor_invoke_static* self, int depth);

void il_factor_invoke_static_generate(il_factor_invoke_static* self, struct enviroment* env, il_context* ilctx);

void il_factor_invoke_static_load(il_factor_invoke_static * self, struct enviroment * env, il_context* ilctx);

struct generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, struct enviroment * env, il_context* ilctx);

char* il_factor_invoke_static_tostr(il_factor_invoke_static* self, struct enviroment* env, il_context* ilctx);

void il_factor_invoke_static_delete(il_factor_invoke_static* self);
#endif