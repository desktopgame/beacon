#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"

struct enviroment;
struct generic_type;
struct operator_overload;
struct method;
//binded? bound?

typedef enum bound_invoke {
	bound_invoke_method_T,
	bound_invoke_subscript_T,
	bound_invoke_undefined_T
} bound_invoke;

typedef struct il_factor_invoke_bound {
	string_view namev;
	Vector* type_args;
	Vector* args;
	union {
		struct method* m;
		subscript_descriptor subscript;
	} u;
	int index;
	struct generic_type* resolved;
	bound_invoke tag;
} il_factor_invoke_bound;

il_factor_invoke_bound* il_factor_invoke_bound_new(string_view namev);

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, struct enviroment* env, call_context* cctx);

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, struct enviroment * env, call_context* cctx);

struct generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, struct enviroment * env, call_context* cctx);

char* il_factor_invoke_bound_tostr(il_factor_invoke_bound* self, struct enviroment* env);

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self);

struct operator_overload* il_factor_invoke_bound_find_set(il_factor_invoke_bound* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex);
#endif