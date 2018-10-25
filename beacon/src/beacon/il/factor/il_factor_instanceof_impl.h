#ifndef BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#define BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#include "../il_factor_interface.h"
struct GenericCache;
struct generic_type;
struct FQCNCache;

typedef struct il_factor_instanceof {
	il_factor* fact;
	struct GenericCache* gcache;
} il_factor_instanceof;

il_factor* WrapILInstanceOf(il_factor_instanceof* self);

il_factor_instanceof* NewILInstanceOf();

void LoadILInstanceOf(il_factor_instanceof* self, Enviroment* env, CallContext* cctx);

void GenerateILInstanceOf(il_factor_instanceof* self, Enviroment* env, CallContext* cctx);

struct generic_type* EvalILInstanceOf(il_factor_instanceof* self, Enviroment* env, CallContext* cctx);

char* ILInstanceOfToString(il_factor_instanceof* self, Enviroment* env);

void DeleteILInstanceOf(il_factor_instanceof* self);
#endif
