#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_stmt* il_stmt_wrap_defer(il_stmt_defer* self) {
	il_stmt* ret = il_stmt_new(ilstmt_defer_T);
	ret->u.defer_ = self;
	return ret;
}

il_stmt_defer* il_stmt_defer_new() {
	il_stmt_defer* ret = (il_stmt_defer*)MEM_MALLOC(sizeof(il_stmt_defer));
	ret->stmt = NULL;
	return ret;
}

void il_stmt_defer_load(il_stmt_defer* self, enviroment* env, call_context* cctx) {
	il_stmt_load(self->stmt, env, cctx);
}

void il_stmt_defer_generate(il_stmt_defer* self, enviroment* env, call_context* cctx) {
	label* lb = opcode_buf_label(env->buf, 0);
	label* lb2 = opcode_buf_label(env->buf, 0);
	opcode_buf_add(env->buf, op_defer_register);
	opcode_buf_add(env->buf, lb2);
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, lb);
	lb2->cursor = opcode_buf_add(env->buf, op_defer_enter);
	il_stmt_generate(self->stmt, env, cctx);
	opcode_buf_add(env->buf, op_defer_exit);
	lb->cursor = opcode_buf_nop(env->buf);
}

void il_stmt_defer_delete(il_stmt_defer* self) {
	il_stmt_delete(self->stmt);
	MEM_FREE(self);
}