#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

ILStatement * WrapILContinue() {
	ILStatement* ret = NewILStatement(ILSTMT_CONTINUE_T);
	return ret;
}

void GenerateILContinue(void * empty, bc_Enviroment * env, CallContext* cctx) {
	if(cctx->Control.WhileStartTable->Length == 0) {
		bc_Panic(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	bc_Label* lab = (bc_Label*)TopVector(cctx->Control.WhileStartTable);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, lab);
}

void LoadILContinue(void * empty, bc_Enviroment * env, CallContext* cctx) {
}

void DeleteILContinue(void * empty) {
}
