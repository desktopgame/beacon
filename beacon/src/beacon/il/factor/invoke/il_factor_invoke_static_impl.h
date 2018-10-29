#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct Enviroment;
struct GenericType;
struct Method;

typedef struct ILInvoke_static {
	StringView namev;
	FQCNCache* fqcn;
	Vector* args;
	Vector* type_args;
	struct Method* m;
	int index;
	struct GenericType* resolved;
} ILInvoke_static;

ILInvoke_static* NewILInvokeStatic(StringView namev);

void GenerateILInvokeStatic(ILInvoke_static* self, Enviroment* env, CallContext* cctx);

void LoadILInvokeStatic(ILInvoke_static * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvokeStatic(ILInvoke_static * self, Enviroment * env, CallContext* cctx);

char* ILInvokeStaticToString(ILInvoke_static* self, Enviroment* env);

void DeleteILInvokeStatic(ILInvoke_static* self);
#endif