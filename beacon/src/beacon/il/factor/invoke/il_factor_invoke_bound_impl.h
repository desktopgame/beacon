#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"

struct Enviroment;
struct GenericType;
struct OperatorOverload;
struct Method;
//binded? bound?

typedef enum bound_invoke {
	BOUND_INVOKE_METHOD_T,
	BOUND_INVOKE_SUBSCRIPT_T,
	BOUND_INVOKE_UNDEFINED_T
} bound_invoke;

typedef struct ILFactor_invoke_bound {
	StringView namev;
	Vector* type_args;
	Vector* args;
	union {
		struct Method* m;
		subscript_descriptor subscript;
	} u;
	int index;
	struct GenericType* resolved;
	bound_invoke tag;
} ILFactor_invoke_bound;

ILFactor_invoke_bound* NewILInvokeBound(StringView namev);

void GenerateILInvokeBound(ILFactor_invoke_bound* self, Enviroment* env, CallContext* cctx);

void LoadILInvokeBound(ILFactor_invoke_bound * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvokeBound(ILFactor_invoke_bound * self, Enviroment * env, CallContext* cctx);

char* ILInvokeBoundToString(ILFactor_invoke_bound* self, Enviroment* env);

void DeleteILInvokeBound(ILFactor_invoke_bound* self);

struct OperatorOverload* FindSetILInvokeBound(ILFactor_invoke_bound* self, ILFactor* value, Enviroment* env, CallContext* cctx, int* outIndex);
#endif