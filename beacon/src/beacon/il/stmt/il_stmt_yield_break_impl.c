#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void il_stmt_yield_break_generate(il_stmt_yield_break* self, enviroment* env, call_context* cctx) {
	AddOpcodeBuf(env->buf, OP_CORO_EXIT);
}

void LoadILYieldBreak(il_stmt_yield_break * self, enviroment* env, call_context* cctx) {
}