#include "il_stmt_break_impl.h"
#include <stdio.h>
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILStatement* bc_WrapILBreak() {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_BREAK_T);
        return ret;
}

void bc_GenerateILBreak(void* empty, bc_Enviroment* env, bc_CallContext* cctx) {
        if (cctx->Control.WhileStartTable->Length == 0) {
                bc_Panic(BCERROR_BREAK_AT_NOT_LOOP_T);
                return;
        }
        bc_Label* lab = (bc_Label*)bc_TopVector(cctx->Control.WhileEndTable);
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, lab);
}

void bc_LoadILBreak(void* empty, bc_Enviroment* env, bc_CallContext* cctx) {}

void bc_DeleteILBreak(void* empty) {}
