#include "il_stmt_while_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include <stdio.h>
#include "../call_context.h"

//proto
static void ILWhile_stmt_delete(bc_VectorItem item);
static void check_condition_type(ILFactor* fact, bc_Enviroment* env, CallContext* cctx);

ILStatement * WrapILWhile(ILWhile * self) {
	ILStatement* ret = NewILStatement(ILSTMT_WHILE_T);
	ret->Kind.While = self;
	return ret;
}

ILWhile * NewILWhile() {
	ILWhile* ret = (ILWhile*)MEM_MALLOC(sizeof(ILWhile));
	ret->Statements = bc_NewVector();
	ret->Condition = NULL;
	return ret;
}

void GenerateILWhile(ILWhile * self, bc_Enviroment * env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	int prev = bc_AddNOPOpcodeBuf(env->Bytecode);
	bc_Label* prevLab = bc_AddLabelOpcodeBuf(env->Bytecode, prev);
	bc_Label* nextLab = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
	bc_PushVector(cctx->Control.WhileStartTable, prevLab);
	bc_PushVector(cctx->Control.WhileEndTable, nextLab);
	//条件を満たさないなら nextLab へ
	GenerateILFactor(self->Condition, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
	bc_AddOpcodeBuf(env->Bytecode, nextLab);
	//全てのステートメントを実行
	for (int i = 0; i < self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)bc_AtVector(self->Statements, i);
		GenerateILStmt(e, env, cctx);
	}
	//prevLab へ行って再判定
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, prevLab);
	bc_PopVector(cctx->Control.WhileStartTable);
	bc_PopVector(cctx->Control.WhileEndTable);
	int next = bc_AddNOPOpcodeBuf(env->Bytecode);
	nextLab->Cursor = next;
	env->Symboles->ScopeDepth--;
}

void DeleteILWhile(ILWhile * self) {
	bc_DeleteVector(self->Statements, ILWhile_stmt_delete);
	DeleteILFactor(self->Condition);
	MEM_FREE(self);
}

void LoadILWhile(ILWhile* self, bc_Enviroment* env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	LoadILFactor(self->Condition, env, cctx);
	for(int i=0; i<self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)bc_AtVector(self->Statements, i);
		LoadILStmt(e, env, cctx);
	}
	check_condition_type(self->Condition, env, cctx);
	env->Symboles->ScopeDepth--;
}

//private
static void ILWhile_stmt_delete(bc_VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void check_condition_type(ILFactor* fact, bc_Enviroment* env, CallContext* cctx) {
	bc_GenericType* cond_T = EvalILFactor(fact, env, cctx);
	if(cond_T->CoreType != BC_TYPE_BOOL) {
		char* condstr = ILFactorToString(fact, env);
		bc_Panic(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}
