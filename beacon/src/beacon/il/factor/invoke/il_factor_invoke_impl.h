#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct enviroment;
struct generic_type;
struct operator_overload;
struct method;

typedef enum instance_invoke {
	INSTANCE_INVOKE_METHOD_T,
	INSTANCE_INVOKE_SUBSCRIPT_T,
	INSTANCE_INVOKE_UNDEFINED_T
} instance_invoke;

typedef struct il_factor_invoke {
	il_factor* receiver;
	Vector* args;
	Vector* type_args;
	string_view namev;
	int index;
	union {
		struct method* m;
		struct operator_overload* opov;
	} u;
	struct generic_type* resolved;
	instance_invoke tag;
} il_factor_invoke;

il_factor_invoke* NewILInvoke(string_view namev);

void il_factor_invoke_generate(il_factor_invoke* self, struct enviroment* env, call_context* cctx);

void LoadILInvoke(il_factor_invoke * self, struct enviroment * env, call_context* cctx);

struct generic_type* EvalILInvoke(il_factor_invoke * self, struct enviroment * env, call_context* cctx);

char* ILInvokeToString(il_factor_invoke* self, struct enviroment* env);

void il_factor_invoke_delete(il_factor_invoke* self);

struct operator_overload* il_factor_invoke_find_set(il_factor_invoke* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex);
#endif