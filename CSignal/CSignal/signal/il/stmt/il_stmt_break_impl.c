#include "il_stmt_break_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_break() {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_break;
	return ret;
}

void il_stmt_break_generate(void * empty, enviroment * env) {
	label* lab = (label*)vector_top(env->whileEnd_vec);
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, lab);
}

void il_stmt_break_load(void * empty, enviroment * env, il_ehandler* eh) {
}

void il_stmt_break_dump(void * empty, int depth) {
	text_putindent(depth);
	printf("break");
	text_putline();
}

void il_stmt_break_delete(void * empty) {
}