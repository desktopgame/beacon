#ifndef BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#define BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#include "../il_factor_interface.h"
struct generic_cache;
struct generic_type;
struct fqcn_cache;

typedef struct il_factor_instanceof {
	il_factor* fact;
	struct generic_cache* gcache;
} il_factor_instanceof;

il_factor* WrapILInstanceOf(il_factor_instanceof* self);

il_factor_instanceof* NewILInstanceOf();

void LoadILInstanceOf(il_factor_instanceof* self, enviroment* env, call_context* cctx);

void il_factor_instanceof_generate(il_factor_instanceof* self, enviroment* env, call_context* cctx);

struct generic_type* EvalILInstanceOf(il_factor_instanceof* self, enviroment* env, call_context* cctx);

char* ILInstanceOfToString(il_factor_instanceof* self, enviroment* env);

void il_factor_instanceof_delete(il_factor_instanceof* self);
#endif
