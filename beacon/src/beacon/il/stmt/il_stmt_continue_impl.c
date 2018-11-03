#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

ILStatement * WrapILContinue() {
	ILStatement* ret = NewILStatement(ILSTMT_CONTINUE_T);
	return ret;
}

void GenerateILContinue(void * empty, Enviroment * env, CallContext* cctx) {
	if(cctx->Control.WhileStartTable->Length == 0) {
		ThrowBCError(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	Label* lab = (Label*)TopVector(cctx->Control.WhileStartTable);
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, lab);
}

void LoadILContinue(void * empty, Enviroment * env, CallContext* cctx) {
}

void DeleteILContinue(void * empty) {
}
