#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

ILStatement* WrapILDefer(ILDefer* self) {
	ILStatement* ret = NewILStatement(ILSTMT_DEFER_T);
	ret->Kind.Defer = self;
	return ret;
}

ILDefer* NewILDefer() {
	ILDefer* ret = (ILDefer*)MEM_MALLOC(sizeof(ILDefer));
	ret->Task = NULL;
	return ret;
}

void LoadILDefer(ILDefer* self, bc_Enviroment* env, CallContext* cctx) {
	LoadILStmt(self->Task, env, cctx);
}

void GenerateILDefer(ILDefer* self, bc_Enviroment* env, CallContext* cctx) {
	bc_Label* lb = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
	bc_Label* lb2 = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
	bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_REGISTER);
	bc_AddOpcodeBuf(env->Bytecode, lb2);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, lb);
	lb2->Cursor = bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_ENTER);
	GenerateILStmt(self->Task, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_EXIT);
	lb->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
}

void DeleteILDefer(ILDefer* self) {
	DeleteILStmt(self->Task);
	MEM_FREE(self);
}