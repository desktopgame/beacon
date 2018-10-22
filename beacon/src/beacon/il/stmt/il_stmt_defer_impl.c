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

void LoadILDefer(il_stmt_defer* self, Enviroment* env, CallContext* cctx) {
	LoadILStmt(self->stmt, env, cctx);
}

void GenerateILDefer(il_stmt_defer* self, Enviroment* env, CallContext* cctx) {
	Label* lb = AddLabelOpcodeBuf(env->Bytecode, 0);
	Label* lb2 = AddLabelOpcodeBuf(env->Bytecode, 0);
	AddOpcodeBuf(env->Bytecode, OP_DEFER_REGISTER);
	AddOpcodeBuf(env->Bytecode, lb2);
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, lb);
	lb2->Cursor = AddOpcodeBuf(env->Bytecode, OP_DEFER_ENTER);
	GenerateILStmt(self->stmt, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_DEFER_EXIT);
	lb->Cursor = AddNOPOpcodeBuf(env->Bytecode);
}

void DeleteILDefer(il_stmt_defer* self) {
	DeleteILStmt(self->stmt);
	MEM_FREE(self);
}