#ifndef BEACON_IL_IL_STM_TRY_H
#define BEACON_IL_IL_STM_TRY_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_stmt_interface.h"

struct enviroment;

typedef struct il_stmt_try {
	Vector* statement_list;
	Vector* catch_list;
} il_stmt_try;

typedef struct il_stmt_catch {
	generic_cache* fqcn;
	string_view namev;
	Vector* statement_list;
} il_stmt_catch;

il_stmt* WrapILTry(il_stmt_try* self);

il_stmt_try* NewILTry();

il_stmt_catch* NewILCatch(string_view namev);

void GenerateILTry(il_stmt_try* self, struct enviroment* env, call_context* cctx);

void il_stmt_catch_generate(il_stmt_catch* self, struct enviroment* env, call_context* cctx);

void LoadILTry(il_stmt_try* self, struct enviroment* env, call_context* cctx);

void LoadILCatch(il_stmt_catch* self, struct enviroment* env, call_context* cctx);

void DeleteILCatch(il_stmt_catch* self);

void DeleteILTry(il_stmt_try* self);
#endif
