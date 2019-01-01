#include "il_stmt_yield_break_impl.h"
#include "../../util/text.h"

void bc_GenerateILYieldBreak(ILStatementYieldBreak* self, bc_Enviroment* env,
                             bc_CallContext* cctx) {
        bc_AddOpcodeBuf(env->Bytecode, OP_CORO_EXIT);
}

void bc_LoadILYieldBreak(ILStatementYieldBreak* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {}