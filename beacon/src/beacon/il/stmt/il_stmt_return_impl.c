#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_return(il_stmt_return * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_return;
	ret->u.return_ = self;
	return ret;
}

il_stmt_return * il_stmt_return_new() {
	il_stmt_return* ret = (il_stmt_return*)MEM_MALLOC(sizeof(il_stmt_return));
	ret->fact = NULL;
	return ret;
}

void il_stmt_return_dump(il_stmt_return * self, int depth) {
	text_putindent(depth);
	text_printf("return");
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_return_generate(il_stmt_return * self, enviroment * env, il_context* ilctx) {
	il_factor_generate(self->fact, env, ilctx);
	opcode_buf_add(env->buf, op_return);
}

void il_stmt_return_load(il_stmt_return * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
	il_factor_load(self->fact, env, ilctx, eh);
}

void il_stmt_return_delete(il_stmt_return * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
