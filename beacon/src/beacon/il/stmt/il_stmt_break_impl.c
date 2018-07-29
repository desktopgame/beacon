#include "il_stmt_break_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_break() {
	il_stmt* ret = il_stmt_new(ilstmt_break);
	return ret;
}

void il_stmt_break_generate(void * empty, enviroment * env, call_context* cctx) {
//	label* lab = cctop_while_end();
//	opcode_buf_add(env->buf, op_goto);
//	opcode_buf_add(env->buf, lab);
}

void il_stmt_break_load(void * empty, enviroment * env, call_context* cctx) {
}

void il_stmt_break_dump(void * empty, int depth) {
	text_putindent(depth);
	text_printf("break");
	text_putline();
}

void il_stmt_break_delete(void * empty) {
}
