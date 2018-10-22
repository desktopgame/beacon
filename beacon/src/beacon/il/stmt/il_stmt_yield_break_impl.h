#ifndef BEACON_IL_YIELD_BREAK_H
#define BEACON_IL_YIELD_BREAK_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

void GenerateILYieldBreak(il_stmt_yield_break* self, Enviroment* env, CallContext* cctx);

void LoadILYieldBreak(il_stmt_yield_break * self, Enviroment* env, CallContext* cctx);
#endif