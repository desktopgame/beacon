#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct enviroment;
struct generic_type;
struct method;

typedef struct il_factor_invoke_static {
	string_view namev;
	fqcn_cache* fqcn;
	vector* args;
	vector* type_args;
	struct method* m;
	int index;
	struct generic_type* resolved;
} il_factor_invoke_static;

il_factor_invoke_static* il_factor_invoke_static_new(string_view namev);

void il_factor_invoke_static_generate(il_factor_invoke_static* self, struct enviroment* env, call_context* cctx);

void il_factor_invoke_static_load(il_factor_invoke_static * self, struct enviroment * env, call_context* cctx);

struct generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, struct enviroment * env, call_context* cctx);

char* il_factor_invoke_static_tostr(il_factor_invoke_static* self, struct enviroment* env);

void il_factor_invoke_static_delete(il_factor_invoke_static* self);
#endif