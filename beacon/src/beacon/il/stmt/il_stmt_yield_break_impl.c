#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void il_stmt_yield_break_generate(il_stmt_yield_break* self, enviroment* env, call_context* cctx) {
	opcode_buf_add(env->buf, op_coro_exit);
}

void il_stmt_yield_break_load(il_stmt_yield_break * self, enviroment* env, call_context* cctx) {
}