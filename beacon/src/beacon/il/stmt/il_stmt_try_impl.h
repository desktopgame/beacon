#ifndef BEACON_IL_IL_STM_TRY_H
#define BEACON_IL_IL_STM_TRY_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct il_stmt_try {
	Vector* statement_list;
	Vector* catch_list;
} il_stmt_try;

typedef struct il_stmt_catch {
	generic_cache* fqcn;
	StringView namev;
	Vector* statement_list;
} il_stmt_catch;

il_stmt* WrapILTry(il_stmt_try* self);

il_stmt_try* NewILTry();

il_stmt_catch* NewILCatch(StringView namev);

void GenerateILTry(il_stmt_try* self, Enviroment* env, CallContext* cctx);

void GenerateILCatch(il_stmt_catch* self, Enviroment* env, CallContext* cctx);

void LoadILTry(il_stmt_try* self, Enviroment* env, CallContext* cctx);

void LoadILCatch(il_stmt_catch* self, Enviroment* env, CallContext* cctx);

void DeleteILCatch(il_stmt_catch* self);

void DeleteILTry(il_stmt_try* self);
#endif
