#include "il_stmt_continue_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_continue() {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_continue;
	return ret;
}

void il_stmt_continue_generate(void * empty, enviroment * env) {
	label* lab = (label*)vector_top(env->whileStart_vec);
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, lab);
}

void il_stmt_continue_load(void * empty, enviroment * env, il_ehandler* eh) {
}

void il_stmt_continue_dump(void * empty, int depth) {
	text_putindent(depth);
	text_printf("continue");
	text_putline();
}

void il_stmt_continue_delete(void * empty) {
}
