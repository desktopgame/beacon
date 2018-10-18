#ifndef BEACON_IL_YIELD_RETURN_H
#define BEACON_IL_YIELD_RETURN_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

typedef struct il_stmt_yield_return {
	il_factor* fact;
} il_stmt_yield_return;

il_stmt* WrapILYieldReturn(il_stmt_yield_return* self);

#define il_stmt_yield_return_new() (MallocILYieldReturn(__FILE__, __LINE__))
il_stmt_yield_return* MallocILYieldReturn(const char* filename, int lineno);

void GenerateILYieldReturn(il_stmt_yield_return* self, Enviroment* env, call_context* cctx);

void LoadILYieldReturn(il_stmt_yield_return * self, Enviroment* env, call_context* cctx);

void DeleteILYieldReturn(il_stmt_yield_return* self);
#endif