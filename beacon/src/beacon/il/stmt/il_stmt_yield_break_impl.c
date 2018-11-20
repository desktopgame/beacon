#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void GenerateILYieldBreak(ILStatementYieldBreak* self, bc_Enviroment* env, CallContext* cctx) {
	bc_AddOpcodeBuf(env->Bytecode, OP_CORO_EXIT);
}

void LoadILYieldBreak(ILStatementYieldBreak * self, bc_Enviroment* env, CallContext* cctx) {
}