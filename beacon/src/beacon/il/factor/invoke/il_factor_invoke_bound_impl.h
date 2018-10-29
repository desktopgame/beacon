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

typedef enum BoundInvokeTag {
	BOUND_INVOKE_METHOD_T,
	BOUND_INVOKE_SUBSCRIPT_T,
	BOUND_INVOKE_UNDEFINED_T
} BoundInvokeTag;

typedef struct ILInvokeBound {
	StringView Name;
	Vector* TypeArgs;
	Vector* Arguments;
	union {
		struct Method* Method;
		SubscriptDescriptor Subscript;
	} Kind;
	int Index;
	struct GenericType* Resolved;
	BoundInvokeTag Tag;
} ILInvokeBound;

ILInvokeBound* NewILInvokeBound(StringView namev);

void GenerateILInvokeBound(ILInvokeBound* self, Enviroment* env, CallContext* cctx);

void LoadILInvokeBound(ILInvokeBound * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvokeBound(ILInvokeBound * self, Enviroment * env, CallContext* cctx);

char* ILInvokeBoundToString(ILInvokeBound* self, Enviroment* env);

void DeleteILInvokeBound(ILInvokeBound* self);

struct OperatorOverload* FindSetILInvokeBound(ILInvokeBound* self, ILFactor* value, Enviroment* env, CallContext* cctx, int* outIndex);
#endif