#include "il_stmt_if_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/namespace.h"
#include "../../vm/opcode_buf.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void DeleteILElifList_impl(bc_VectorItem item);
static void DeleteILIf_stmt(bc_VectorItem item);
static void check_condition_type(bc_ILFactor* fact, bc_Enviroment* env, bc_CallContext* cctx);

bc_ILStatement * WrapILIf(ILIf * self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_IF_T);
	ret->Kind.If = self;
	return ret;
}

ILIf * NewILIf() {
	ILIf* ret = (ILIf*)MEM_MALLOC(sizeof(ILIf));
	ret->Condition = NULL;
	ret->ElifList = bc_NewVector();
	ret->Else = NewILElse();
	ret->Body = bc_NewVector();
	return ret;
}

ILElif * NewILElif() {
	ILElif* ret = (ILElif*)MEM_MALLOC(sizeof(ILElif));
	ret->Condition = NULL;
	ret->Body = bc_NewVector();
	return ret;
}

bc_Vector * NewILElifList() {
	return bc_NewVector();
}

ILElse * NewILElse() {
	ILElse* ret = (ILElse*)MEM_MALLOC(sizeof(ILElse));
	ret->Body = bc_NewVector();
	return ret;
}

void PushILElifList(bc_Vector * self, ILElif * child) {
	bc_PushVector(self, child);
}

void GenerateILIf(ILIf * self, bc_Enviroment* env, bc_CallContext* cctx) {
	//if(...)
	env->Symboles->ScopeDepth++;
	bc_GenerateILFactor(self->Condition, env, cctx);
	bc_Label* l1 = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
	bc_Label* tail = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
	// { ... }
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
	bc_AddOpcodeBuf(env->Bytecode, l1);
	for (int i = 0; i < self->Body->Length; i++) {
		bc_ILStatement* stmt = (bc_ILStatement*)bc_AtVector(self->Body, i);
		bc_GenerateILStmt(stmt, env, cctx);
	}
	//条件が満たされて実行されたら最後までジャンプ
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
	bc_AddOpcodeBuf(env->Bytecode, tail);
	l1->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
	// elif(...)
	for (int i = 0; i < self->ElifList->Length; i++) {
		ILElif* elif = (ILElif*)bc_AtVector(self->ElifList, i);
		bc_GenerateILFactor(elif->Condition, env, cctx);
		bc_Label* l2 = bc_AddLabelOpcodeBuf(env->Bytecode, -1);
		// { ... }
		bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
		bc_AddOpcodeBuf(env->Bytecode, l2);
		for (int j = 0; j < elif->Body->Length; j++) {
			bc_ILStatement* stmt = (bc_ILStatement*)bc_AtVector(elif->Body, j);
			bc_GenerateILStmt(stmt, env, cctx);
		}
		//条件が満たされて実行されたら最後までジャンプ
		bc_AddOpcodeBuf(env->Bytecode, OP_GOTO);
		bc_AddOpcodeBuf(env->Bytecode, tail);
		l2->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
	}
	// else { ... }
	if (self->Else == NULL ||
		self->Else->Body->Length == 0) {
		tail->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
	} else {
		for (int i = 0; i < self->Else->Body->Length; i++) {
			bc_ILStatement* stmt = (bc_ILStatement*)bc_AtVector(self->Else->Body, i);
			bc_GenerateILStmt(stmt, env, cctx);
		}
		tail->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
	}
	env->Symboles->ScopeDepth--;
}

void LoadILIf(ILIf * self, bc_Enviroment* env, bc_CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	bc_LoadILFactor(self->Condition, env, cctx);
	for(int i=0; i<self->Body->Length; i++) {
		bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(self->Body, i);
		bc_LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	for(int i=0; i<self->ElifList->Length; i++) {
		ILElif* e = (ILElif*)bc_AtVector(self->ElifList, i);
		bc_LoadILFactor(e->Condition, env, cctx);
		for(int j=0; j<e->Body->Length; j++) {
			bc_ILStatement* st = (bc_ILStatement*)bc_AtVector(e->Body, j);
			bc_LoadILStmt(st, env, cctx);
			BC_ERROR();
		}
		BC_ERROR();
	}
	for(int i=0; i<self->Else->Body->Length; i++) {
		bc_ILStatement* e = (bc_ILStatement*)bc_AtVector(self->Else->Body, i);
		bc_LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	//条件が bool を返さない
	BC_ERROR();
	check_condition_type(self->Condition, env, cctx);
	for(int i=0; i<self->ElifList->Length; i++) {
		ILElif* elif = bc_AtVector(self->ElifList, i);
		check_condition_type(elif->Condition, env, cctx);
		BC_ERROR();
	}
	env->Symboles->ScopeDepth--;
}

void DeleteILIf(ILIf * self) {
	bc_DeleteVector(self->ElifList, DeleteILElifList_impl);
	DeleteILElse(self->Else);
	bc_DeleteVector(self->Body, DeleteILIf_stmt);
	bc_DeleteILFactor(self->Condition);
	MEM_FREE(self);
}

void DeleteILElif(ILElif * self) {
	bc_DeleteILFactor(self->Condition);
	bc_DeleteVector(self->Body, DeleteILIf_stmt);
	MEM_FREE(self);
}

void DeleteILElifList(bc_Vector * self) {
	bc_DeleteVector(self, DeleteILElifList_impl);
}

void DeleteILElse(ILElse * self) {
	bc_DeleteVector(self->Body, DeleteILIf_stmt);
	MEM_FREE(self);
}

//private
static void DeleteILElifList_impl(bc_VectorItem item) {
	ILElif* el = (ILElif*)item;
	DeleteILElif(el);
}

static void DeleteILIf_stmt(bc_VectorItem item) {
	bc_ILStatement* e = (bc_ILStatement*)item;
	bc_DeleteILStmt(e);
}

static void check_condition_type(bc_ILFactor* fact, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* cond_T = bc_EvalILFactor(fact, env, cctx);
	if(cond_T->CoreType != BC_TYPE_BOOL) {
		char* condstr = bc_ILFactorToString(fact, env);
		bc_Panic(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}