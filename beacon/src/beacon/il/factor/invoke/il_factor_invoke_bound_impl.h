#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"

struct Enviroment;
struct generic_type;
struct operator_overload;
struct method;
//binded? bound?

typedef enum bound_invoke {
	BOUND_INVOKE_METHOD_T,
	BOUND_INVOKE_SUBSCRIPT_T,
	BOUND_INVOKE_UNDEFINED_T
} bound_invoke;

typedef struct il_factor_invoke_bound {
	StringView namev;
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

il_factor_invoke_bound* NewILInvokeBound(StringView namev);

void GenerateILInvokeBound(il_factor_invoke_bound* self, Enviroment* env, call_context* cctx);

void LoadILInvokeBound(il_factor_invoke_bound * self, Enviroment * env, call_context* cctx);

struct generic_type* EvalILInvokeBound(il_factor_invoke_bound * self, Enviroment * env, call_context* cctx);

char* ILInvokeBoundToString(il_factor_invoke_bound* self, Enviroment* env);

void DeleteILInvokeBound(il_factor_invoke_bound* self);

struct operator_overload* FindSetILInvokeBound(il_factor_invoke_bound* self, il_factor* value, Enviroment* env, call_context* cctx, int* outIndex);
#endif