#ifndef BEACON_IL_YIELD_RETURN_H
#define BEACON_IL_YIELD_RETURN_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

typedef struct il_stmt_yield_return {
	il_factor* fact;
} il_stmt_yield_return;

il_stmt* WrapILYieldReturn(il_stmt_yield_return* self);

#define il_stmt_yield_return_new() (il_stmt_yield_return_malloc(__FILE__, __LINE__))
il_stmt_yield_return* il_stmt_yield_return_malloc(const char* filename, int lineno);

void il_stmt_yield_return_generate(il_stmt_yield_return* self, enviroment* env, call_context* cctx);

void LoadILYieldReturn(il_stmt_yield_return * self, enviroment* env, call_context* cctx);

void il_stmt_yield_return_delete(il_stmt_yield_return* self);
#endif