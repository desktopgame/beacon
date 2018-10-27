#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void GenerateILYieldBreak(ILStatement_yield_break* self, Enviroment* env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_CORO_EXIT);
}

void LoadILYieldBreak(ILStatement_yield_break * self, Enviroment* env, CallContext* cctx) {
}