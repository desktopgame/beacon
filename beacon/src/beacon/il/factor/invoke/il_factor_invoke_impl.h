#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct enviroment;
struct generic_type;
struct operator_overload;
struct method;

typedef enum instance_invoke_T {
	instance_invoke_method_T,
	instance_invoke_subscript_T,
	instance_invoke_undefined_T
} instance_invoke_T;

typedef struct il_factor_invoke {
	il_factor* receiver;
	vector* args;
	vector* type_args;
	string_view namev;
	int index;
	union {
		struct method* m;
		struct operator_overload* opov;
	} u;
	struct generic_type* resolved;
	instance_invoke_T tag;
} il_factor_invoke;

il_factor_invoke* il_factor_invoke_new(string_view namev);

void il_factor_invoke_dump(il_factor_invoke* self, int depth);

void il_factor_invoke_generate(il_factor_invoke* self, struct enviroment* env, call_context* cctx);

void il_factor_invoke_load(il_factor_invoke * self, struct enviroment * env, call_context* cctx);

struct generic_type* il_factor_invoke_eval(il_factor_invoke * self, struct enviroment * env, call_context* cctx);

char* il_factor_invoke_tostr(il_factor_invoke* self, struct enviroment* env);

void il_factor_invoke_delete(il_factor_invoke* self);

struct operator_overload* il_factor_invoke_find_set(il_factor_invoke* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex);
#endif