#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void GenerateILYieldBreak(ILStatementYieldBreak* self, Enviroment* env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_CORO_EXIT);
}

void LoadILYieldBreak(ILStatementYieldBreak * self, Enviroment* env, CallContext* cctx) {
}