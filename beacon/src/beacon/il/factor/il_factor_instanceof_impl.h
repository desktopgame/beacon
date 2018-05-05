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

il_factor* il_factor_wrap_instanceof(il_factor_instanceof* self);

il_factor_instanceof* il_factor_instanceof_new();

void il_factor_instanceof_dump(il_factor_instanceof* self, int depth);

void il_factor_instanceof_load(il_factor_instanceof* self, enviroment* env, il_context* ilctx);

void il_factor_instanceof_generate(il_factor_instanceof* self, enviroment* env, il_context* ilctx);

struct generic_type* il_factor_instanceof_eval(il_factor_instanceof* self, enviroment* env, il_context* ilctx);

char* il_factor_instanceof_tostr(il_factor_instanceof* self, enviroment* env, il_context* ilctx);

void il_factor_instanceof_delete(il_factor_instanceof* self);
#endif
