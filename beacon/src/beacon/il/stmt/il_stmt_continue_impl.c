#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_continue() {
	il_stmt* ret = il_stmt_new(ILSTMT_CONTINUE_T);
	return ret;
}

void il_stmt_continue_generate(void * empty, enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->length == 0) {
		bc_error_throw(BCERROR_CONTINUE_AT_NOT_LOOP_T);
		return;
	}
	label* lab = (label*)TopVector(cctx->control.while_start);
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, lab);
}

void il_stmt_continue_load(void * empty, enviroment * env, call_context* cctx) {
}

void il_stmt_continue_delete(void * empty) {
}
