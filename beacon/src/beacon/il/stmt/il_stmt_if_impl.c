#include "il_stmt_if_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/namespace.h"
#include "../../vm/opcode_buf.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void DeleteILElifList_impl(VectorItem item);
static void DeleteILIf_stmt(VectorItem item);
static void check_condition_type(ILFactor* fact, Enviroment* env, CallContext* cctx);

ILStatement * WrapILIf(ILIf * self) {
	ILStatement* ret = NewILStatement(ILSTMT_IF_T);
	ret->Kind.If = self;
	return ret;
}

ILIf * NewILIf() {
	ILIf* ret = (ILIf*)MEM_MALLOC(sizeof(ILIf));
	ret->Condition = NULL;
	ret->ElifList = NewVector();
	ret->Else = NewILElse();
	ret->Body = NewVector();
	return ret;
}

ILElif * NewILElif() {
	ILElif* ret = (ILElif*)MEM_MALLOC(sizeof(ILElif));
	ret->Condition = NULL;
	ret->Body = NewVector();
	return ret;
}

Vector * NewILElifList() {
	return NewVector();
}

ILElse * NewILElse() {
	ILElse* ret = (ILElse*)MEM_MALLOC(sizeof(ILElse));
	ret->Body = NewVector();
	return ret;
}

void PushILElifList(Vector * self, ILElif * child) {
	PushVector(self, child);
}

void GenerateILIf(ILIf * self, Enviroment* env, CallContext* cctx) {
	//if(...)
	env->Symboles->ScopeDepth++;
	GenerateILFactor(self->Condition, env, cctx);
	Label* l1 = AddLabelOpcodeBuf(env->Bytecode, -1);
	Label* tail = AddLabelOpcodeBuf(env->Bytecode, -1);
	// { ... }
	AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
	AddOpcodeBuf(env->Bytecode, l1);
	for (int i = 0; i < self->Body->Length; i++) {
		ILStatement* stmt = (ILStatement*)AtVector(self->Body, i);
		GenerateILStmt(stmt, env, cctx);
	}
	//条件が満たされて実行されたら最後までジャンプ
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, tail);
	l1->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	// elif(...)
	for (int i = 0; i < self->ElifList->Length; i++) {
		ILElif* elif = (ILElif*)AtVector(self->ElifList, i);
		GenerateILFactor(elif->Condition, env, cctx);
		Label* l2 = AddLabelOpcodeBuf(env->Bytecode, -1);
		// { ... }
		AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
		AddOpcodeBuf(env->Bytecode, l2);
		for (int j = 0; j < elif->Body->Length; j++) {
			ILStatement* stmt = (ILStatement*)AtVector(elif->Body, j);
			GenerateILStmt(stmt, env, cctx);
		}
		//条件が満たされて実行されたら最後までジャンプ
		AddOpcodeBuf(env->Bytecode, OP_GOTO);
		AddOpcodeBuf(env->Bytecode, tail);
		l2->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	}
	// else { ... }
	if (self->Else == NULL ||
		self->Else->Body->Length == 0) {
		tail->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	} else {
		for (int i = 0; i < self->Else->Body->Length; i++) {
			ILStatement* stmt = (ILStatement*)AtVector(self->Else->Body, i);
			GenerateILStmt(stmt, env, cctx);
		}
		tail->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	}
	env->Symboles->ScopeDepth--;
}

void LoadILIf(ILIf * self, Enviroment* env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	LoadILFactor(self->Condition, env, cctx);
	for(int i=0; i<self->Body->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Body, i);
		LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	for(int i=0; i<self->ElifList->Length; i++) {
		ILElif* e = (ILElif*)AtVector(self->ElifList, i);
		LoadILFactor(e->Condition, env, cctx);
		for(int j=0; j<e->Body->Length; j++) {
			ILStatement* st = (ILStatement*)AtVector(e->Body, j);
			LoadILStmt(st, env, cctx);
			BC_ERROR();
		}
		BC_ERROR();
	}
	for(int i=0; i<self->Else->Body->Length; i++) {
		ILStatement* e = (ILStatement*)AtVector(self->Else->Body, i);
		LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	//条件が bool を返さない
	BC_ERROR();
	check_condition_type(self->Condition, env, cctx);
	for(int i=0; i<self->ElifList->Length; i++) {
		ILElif* elif = AtVector(self->ElifList, i);
		check_condition_type(elif->Condition, env, cctx);
		BC_ERROR();
	}
	env->Symboles->ScopeDepth--;
}

void DeleteILIf(ILIf * self) {
	DeleteVector(self->ElifList, DeleteILElifList_impl);
	DeleteILElse(self->Else);
	DeleteVector(self->Body, DeleteILIf_stmt);
	DeleteILFactor(self->Condition);
	MEM_FREE(self);
}

void DeleteILElif(ILElif * self) {
	DeleteILFactor(self->Condition);
	DeleteVector(self->Body, DeleteILIf_stmt);
	MEM_FREE(self);
}

void DeleteILElifList(Vector * self) {
	DeleteVector(self, DeleteILElifList_impl);
}

void DeleteILElse(ILElse * self) {
	DeleteVector(self->Body, DeleteILIf_stmt);
	MEM_FREE(self);
}

//private
static void DeleteILElifList_impl(VectorItem item) {
	ILElif* el = (ILElif*)item;
	DeleteILElif(el);
}

static void DeleteILIf_stmt(VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}

static void check_condition_type(ILFactor* fact, Enviroment* env, CallContext* cctx) {
	bc_GenericType* cond_T = EvalILFactor(fact, env, cctx);
	if(cond_T->CoreType != BC_TYPE_BOOL) {
		char* condstr = ILFactorToString(fact, env);
		bc_Panic(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}