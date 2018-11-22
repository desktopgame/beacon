#include "il_stmt_defer_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILStatement* bc_WrapILDefer(bc_ILDefer* self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_DEFER_T);
	ret->Kind.Defer = self;
	return ret;
}

bc_ILDefer* bc_NewILDefer() {
	bc_ILDefer* ret = (bc_ILDefer*)MEM_MALLOC(sizeof(bc_ILDefer));
	ret->Task = NULL;
	return ret;
}

void bc_LoadILDefer(bc_ILDefer* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILStmt(self->Task, env, cctx);
}

void bc_GenerateILDefer(bc_ILDefer* self, bc_Enviroment* env, bc_CallContext* cctx) {
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

void bc_DeleteILDefer(bc_ILDefer* self) {
	bc_DeleteILStmt(self->Task);
	MEM_FREE(self);
}