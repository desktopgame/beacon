#include "il_stmt_while_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include <stdio.h>
#include "../call_context.h"

//proto
static void ILWhile_stmt_delete(VectorItem item);
static void check_condition_type(ILFactor* fact, Enviroment* env, CallContext* cctx);

ILStatement * WrapILWhile(ILWhile * self) {
	ILStatement* ret = NewILStatement(ILSTMT_WHILE_T);
	ret->Kind.While = self;
	return ret;
}

ILWhile * NewILWhile() {
	ILWhile* ret = (ILWhile*)MEM_MALLOC(sizeof(ILWhile));
	ret->Statements = NewVector();
	ret->Condition = NULL;
	return ret;
}

void GenerateILWhile(ILWhile * self, Enviroment * env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	int prev = AddNOPOpcodeBuf(env->Bytecode);
	Label* prevLab = AddLabelOpcodeBuf(env->Bytecode, prev);
	Label* nextLab = AddLabelOpcodeBuf(env->Bytecode, -1);
	PushVector(cctx->Control.WhileStartTable, prevLab);
	PushVector(cctx->Control.WhileEndTable, nextLab);
	//条件を満たさないなら nextLab へ
	GenerateILFactor(self->Condition, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
	AddOpcodeBuf(env->Bytecode, nextLab);
	//全てのステートメントを実行
	for (int i = 0; i < self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Statements, i);
		GenerateILStmt(e, env, cctx);
	}
	//prevLab へ行って再判定
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, prevLab);
	PopVector(cctx->Control.WhileStartTable);
	PopVector(cctx->Control.WhileEndTable);
	int next = AddNOPOpcodeBuf(env->Bytecode);
	nextLab->Cursor = next;
	env->Symboles->ScopeDepth--;
}

void DeleteILWhile(ILWhile * self) {
	DeleteVector(self->Statements, ILWhile_stmt_delete);
	DeleteILFactor(self->Condition);
	MEM_FREE(self);
}

void LoadILWhile(ILWhile* self, Enviroment* env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	LoadILFactor(self->Condition, env, cctx);
	for(int i=0; i<self->Statements->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Statements, i);
		LoadILStmt(e, env, cctx);
	}
	check_condition_type(self->Condition, env, cctx);
	env->Symboles->ScopeDepth--;
}

//private
static void ILWhile_stmt_delete(VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void check_condition_type(ILFactor* fact, Enviroment* env, CallContext* cctx) {
	GenericType* cond_T = EvalILFactor(fact, env, cctx);
	if(cond_T->CoreType != TYPE_BOOL) {
		char* condstr = ILFactorToString(fact, env);
		bc_Panic(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}
