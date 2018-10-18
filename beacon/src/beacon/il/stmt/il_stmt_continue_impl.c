#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * WrapILContinue() {
	il_stmt* ret = il_stmt_new(ILSTMT_CONTINUE_T);
	return ret;
}

void GenerateILContinue(void * empty, Enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->Length == 0) {
		ThrowBCError(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	Label* lab = (Label*)TopVector(cctx->control.while_start);
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, lab);
}

void LoadILContinue(void * empty, Enviroment * env, call_context* cctx) {
}

void DeleteILContinue(void * empty) {
}
