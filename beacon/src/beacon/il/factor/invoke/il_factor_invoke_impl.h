#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct Enviroment;
struct GenericType;
struct OperatorOverload;
struct Method;

typedef enum instance_invoke {
	INSTANCE_INVOKE_METHOD_T,
	INSTANCE_INVOKE_SUBSCRIPT_T,
	INSTANCE_INVOKE_UNDEFINED_T
} instance_invoke;

typedef struct ILFactor_invoke {
	ILFactor* receiver;
	Vector* args;
	Vector* type_args;
	StringView namev;
	int index;
	union {
		struct Method* m;
		struct OperatorOverload* opov;
	} u;
	struct GenericType* resolved;
	instance_invoke tag;
} ILFactor_invoke;

ILFactor_invoke* NewILInvoke(StringView namev);

void GenerateILInvoke(ILFactor_invoke* self, Enviroment* env, CallContext* cctx);

void LoadILInvoke(ILFactor_invoke * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvoke(ILFactor_invoke * self, Enviroment * env, CallContext* cctx);

char* ILInvokeToString(ILFactor_invoke* self, Enviroment* env);

void DeleteILInvoke(ILFactor_invoke* self);

struct OperatorOverload* FindSetILInvoke(ILFactor_invoke* self, ILFactor* value, Enviroment* env, CallContext* cctx, int* outIndex);
#endif