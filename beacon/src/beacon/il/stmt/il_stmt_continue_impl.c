#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * WrapILContinue() {
	il_stmt* ret = il_stmt_new(ILSTMT_CONTINUE_T);
	return ret;
}

void GenerateILContinue(void * empty, enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->Length == 0) {
		ThrowBCError(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	label* lab = (label*)TopVector(cctx->control.while_start);
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, lab);
}

void LoadILContinue(void * empty, enviroment * env, call_context* cctx) {
}

void DeleteILContinue(void * empty) {
}
