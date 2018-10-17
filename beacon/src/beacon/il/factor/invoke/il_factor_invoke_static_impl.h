#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct enviroment;
struct generic_type;
struct method;

typedef struct il_factor_invoke_static {
	StringView namev;
	fqcn_cache* fqcn;
	Vector* args;
	Vector* type_args;
	struct method* m;
	int index;
	struct generic_type* resolved;
} il_factor_invoke_static;

il_factor_invoke_static* NewILInvokeStatic(StringView namev);

void GenerateILInvokeStatic(il_factor_invoke_static* self, struct enviroment* env, call_context* cctx);

void LoadILInvokeStatic(il_factor_invoke_static * self, struct enviroment * env, call_context* cctx);

struct generic_type* EvalILInvokeStatic(il_factor_invoke_static * self, struct enviroment * env, call_context* cctx);

char* ILInvokeStaticToString(il_factor_invoke_static* self, struct enviroment* env);

void DeleteILInvokeStatic(il_factor_invoke_static* self);
#endif