#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILStatement* WrapILDefer(ILDefer* self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_DEFER_T);
	ret->Kind.Defer = self;
	return ret;
}

ILDefer* NewILDefer() {
	ILDefer* ret = (ILDefer*)MEM_MALLOC(sizeof(ILDefer));
	ret->Task = NULL;
	return ret;
}

void LoadILDefer(ILDefer* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILStmt(self->Task, env, cctx);
}

void GenerateILDefer(ILDefer* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_Label* lb = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
	bc_Label* lb2 = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
	bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_REGISTER);
	bc_AddOpcodeBuf(env->Bytecode, lb2);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, lb);
	lb2->Cursor = bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_ENTER);
	bc_GenerateILStmt(self->Task, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_DEFER_EXIT);
	lb->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
}

void DeleteILDefer(ILDefer* self) {
	bc_DeleteILStmt(self->Task);
	MEM_FREE(self);
}