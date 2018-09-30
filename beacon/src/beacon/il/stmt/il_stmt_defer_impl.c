#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_stmt* WrapILDefer(il_stmt_defer* self) {
	il_stmt* ret = il_stmt_new(ILSTMT_DEFER_T);
	ret->u.defer_ = self;
	return ret;
}

il_stmt_defer* NewILDefer() {
	il_stmt_defer* ret = (il_stmt_defer*)MEM_MALLOC(sizeof(il_stmt_defer));
	ret->stmt = NULL;
	return ret;
}

void LoadILDefer(il_stmt_defer* self, enviroment* env, call_context* cctx) {
	LoadILStmt(self->stmt, env, cctx);
}

void il_stmt_defer_generate(il_stmt_defer* self, enviroment* env, call_context* cctx) {
	label* lb = AddLabelOpcodeBuf(env->buf, 0);
	label* lb2 = AddLabelOpcodeBuf(env->buf, 0);
	AddOpcodeBuf(env->buf, OP_DEFER_REGISTER);
	AddOpcodeBuf(env->buf, lb2);
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, lb);
	lb2->cursor = AddOpcodeBuf(env->buf, OP_DEFER_ENTER);
	GenerateILStmt(self->stmt, env, cctx);
	AddOpcodeBuf(env->buf, OP_DEFER_EXIT);
	lb->cursor = AddNOPOpcodeBuf(env->buf);
}

void DeleteILDefer(il_stmt_defer* self) {
	DeleteILStmt(self->stmt);
	MEM_FREE(self);
}