#include "il_stmt_continue_impl.h"
#include <stdio.h>
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILStatement* bc_WrapILContinue() {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_CONTINUE_T);
        return ret;
}

void bc_GenerateILContinue(void* empty, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        if (cctx->Control.WhileStartTable->Length == 0) {
                bc_Panic(BCERROR_CONTINUE_AT_NOT_LOOP_T);
                return;
        }
        bc_Label* lab = (bc_Label*)bc_TopVector(cctx->Control.WhileStartTable);
        bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
        bc_AddOpcodeBuf(env->Bytecode, lab);
}

void bc_LoadILContinue(void* empty, bc_Enviroment* env, bc_CallContext* cctx) {}

void bc_DeleteILContinue(void* empty) {}
