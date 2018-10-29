#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct Enviroment;
struct GenericType;
struct Method;

typedef struct ILInvokeStatic {
	StringView Name;
	FQCNCache* FQCN;
	Vector* Arguments;
	Vector* TypeArgs;
	struct Method* Method;
	int Index;
	struct GenericType* Resolved;
} ILInvokeStatic;

ILInvokeStatic* NewILInvokeStatic(StringView namev);

void GenerateILInvokeStatic(ILInvokeStatic* self, Enviroment* env, CallContext* cctx);

void LoadILInvokeStatic(ILInvokeStatic * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvokeStatic(ILInvokeStatic * self, Enviroment * env, CallContext* cctx);

char* ILInvokeStaticToString(ILInvokeStatic* self, Enviroment* env);

void DeleteILInvokeStatic(ILInvokeStatic* self);
#endif