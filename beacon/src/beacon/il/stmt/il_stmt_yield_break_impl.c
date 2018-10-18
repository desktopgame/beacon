#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void GenerateILYieldBreak(il_stmt_yield_break* self, Enviroment* env, call_context* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_CORO_EXIT);
}

void LoadILYieldBreak(il_stmt_yield_break * self, Enviroment* env, call_context* cctx) {
}