#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

bc_ILStatement * WrapILContinue() {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_CONTINUE_T);
	return ret;
}

void GenerateILContinue(void * empty, bc_Enviroment * env, bc_CallContext* cctx) {
	if(cctx->Control.WhileStartTable->Length == 0) {
		bc_Panic(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	bc_Label* lab = (bc_Label*)bc_TopVector(cctx->Control.WhileStartTable);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, lab);
}

void LoadILContinue(void * empty, bc_Enviroment * env, bc_CallContext* cctx) {
}

void DeleteILContinue(void * empty) {
}
