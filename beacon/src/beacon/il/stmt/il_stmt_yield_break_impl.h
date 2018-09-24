#ifndef BEACON_IL_YIELD_BREAK_H
#define BEACON_IL_YIELD_BREAK_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

void il_stmt_yield_break_generate(il_stmt_yield_break* self, enviroment* env, call_context* cctx);

void il_stmt_yield_break_load(il_stmt_yield_break * self, enviroment* env, call_context* cctx);
#endif