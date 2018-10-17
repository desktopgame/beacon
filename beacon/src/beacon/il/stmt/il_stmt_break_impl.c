#include "il_stmt_break_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * WrapILBreak() {
	il_stmt* ret = il_stmt_new(ILSTMT_BREAK_T);
	return ret;
}

void GenerateILBreak(void * empty, enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->Length == 0) {
		ThrowBCError(BCERROR_BREAK_AT_NOT_LOOP_T);
		return;
	}
	Label* lab = (Label*)TopVector(cctx->control.while_end);
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, lab);
}

void LoadILBreak(void * empty, enviroment * env, call_context* cctx) {
}

void DeleteILBreak(void * empty) {
}
