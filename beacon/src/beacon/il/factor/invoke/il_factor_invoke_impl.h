#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct Enviroment;
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
	StringView namev;
	int index;
	union {
		struct method* m;
		struct operator_overload* opov;
	} u;
	struct generic_type* resolved;
	instance_invoke tag;
} il_factor_invoke;

il_factor_invoke* NewILInvoke(StringView namev);

void GenerateILInvoke(il_factor_invoke* self, Enviroment* env, CallContext* cctx);

void LoadILInvoke(il_factor_invoke * self, Enviroment * env, CallContext* cctx);

struct generic_type* EvalILInvoke(il_factor_invoke * self, Enviroment * env, CallContext* cctx);

char* ILInvokeToString(il_factor_invoke* self, Enviroment* env);

void DeleteILInvoke(il_factor_invoke* self);

struct operator_overload* FindSetILInvoke(il_factor_invoke* self, il_factor* value, Enviroment* env, CallContext* cctx, int* outIndex);
#endif