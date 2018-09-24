#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_continue() {
	il_stmt* ret = il_stmt_new(ilstmt_continue_T);
	return ret;
}

void il_stmt_continue_generate(void * empty, enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->length == 0) {
		bc_error_throw(bcerror_continue_at_not_loop_T);
		return;
	}
	label* lab = (label*)vector_top(cctx->control.while_start);
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, lab);
}

void il_stmt_continue_load(void * empty, enviroment * env, call_context* cctx) {
}

void il_stmt_continue_delete(void * empty) {
}
