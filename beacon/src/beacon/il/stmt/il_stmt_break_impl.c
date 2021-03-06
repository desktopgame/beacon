#include "il_stmt_break_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_break() {
	il_stmt* ret = il_stmt_new(ilstmt_break_T);
	return ret;
}

void il_stmt_break_generate(void * empty, enviroment * env, call_context* cctx) {
	if(cctx->control.while_start->length == 0) {
		bc_error_throw(bcerror_break_at_not_loop_T);
		return;
	}
	label* lab = (label*)vector_top(cctx->control.while_end);
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, lab);
}

void il_stmt_break_load(void * empty, enviroment * env, call_context* cctx) {
}

void il_stmt_break_dump(void * empty, int depth) {
	io_printi(depth);
	printf("break");
	io_println();
}

void il_stmt_break_delete(void * empty) {
}
