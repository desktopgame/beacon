#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

ILStatement* WrapILDefer(ILDefer* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_DEFER_T);
	ret->u.defer_ = self;
	return ret;
}

ILDefer* NewILDefer() {
	ILDefer* ret = (ILDefer*)MEM_MALLOC(sizeof(ILDefer));
	ret->Task = NULL;
	return ret;
}

void LoadILDefer(ILDefer* self, Enviroment* env, CallContext* cctx) {
	LoadILStmt(self->Task, env, cctx);
}

void GenerateILDefer(ILDefer* self, Enviroment* env, CallContext* cctx) {
	Label* lb = AddLabelOpcodeBuf(env->Bytecode, 0);
	Label* lb2 = AddLabelOpcodeBuf(env->Bytecode, 0);
	AddOpcodeBuf(env->Bytecode, OP_DEFER_REGISTER);
	AddOpcodeBuf(env->Bytecode, lb2);
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, lb);
	lb2->Cursor = AddOpcodeBuf(env->Bytecode, OP_DEFER_ENTER);
	GenerateILStmt(self->Task, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_DEFER_EXIT);
	lb->Cursor = AddNOPOpcodeBuf(env->Bytecode);
}

void DeleteILDefer(ILDefer* self) {
	DeleteILStmt(self->Task);
	MEM_FREE(self);
}