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
static void check_condition_type(il_factor* fact, Enviroment* env, CallContext* cctx);

il_stmt * WrapILIf(il_stmt_if * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_IF_T);
	ret->u.if_ = self;
	return ret;
}

il_stmt_if * NewILIf() {
	il_stmt_if* ret = (il_stmt_if*)MEM_MALLOC(sizeof(il_stmt_if));
	ret->condition = NULL;
	ret->elif_list = NewVector();
	ret->else_body = NewILElse();
	ret->body = NewVector();
	return ret;
}

il_stmt_elif * NewILElif() {
	il_stmt_elif* ret = (il_stmt_elif*)MEM_MALLOC(sizeof(il_stmt_elif));
	ret->condition = NULL;
	ret->body = NewVector();
	return ret;
}

Vector * NewILElifList() {
	return NewVector();
}

il_stmt_else * NewILElse() {
	il_stmt_else* ret = (il_stmt_else*)MEM_MALLOC(sizeof(il_stmt_else));
	ret->body = NewVector();
	return ret;
}

void PushILElifList(Vector * self, il_stmt_elif * child) {
	PushVector(self, child);
}

void GenerateILIf(il_stmt_if * self, Enviroment* env, CallContext* cctx) {
	//if(...)
	env->Symboles->ScopeDepth++;
	GenerateILFactor(self->condition, env, cctx);
	Label* l1 = AddLabelOpcodeBuf(env->Bytecode, -1);
	Label* tail = AddLabelOpcodeBuf(env->Bytecode, -1);
	// { ... }
	AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
	AddOpcodeBuf(env->Bytecode, l1);
	for (int i = 0; i < self->body->Length; i++) {
		il_stmt* stmt = (il_stmt*)AtVector(self->body, i);
		GenerateILStmt(stmt, env, cctx);
	}
	//条件が満たされて実行されたら最後までジャンプ
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, tail);
	l1->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	// elif(...)
	for (int i = 0; i < self->elif_list->Length; i++) {
		il_stmt_elif* elif = (il_stmt_elif*)AtVector(self->elif_list, i);
		GenerateILFactor(elif->condition, env, cctx);
		Label* l2 = AddLabelOpcodeBuf(env->Bytecode, -1);
		// { ... }
		AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_FALSE);
		AddOpcodeBuf(env->Bytecode, l2);
		for (int j = 0; j < elif->body->Length; j++) {
			il_stmt* stmt = (il_stmt*)AtVector(elif->body, j);
			GenerateILStmt(stmt, env, cctx);
		}
		//条件が満たされて実行されたら最後までジャンプ
		AddOpcodeBuf(env->Bytecode, OP_GOTO);
		AddOpcodeBuf(env->Bytecode, tail);
		l2->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	}
	// else { ... }
	if (self->else_body == NULL ||
		self->else_body->body->Length == 0) {
		tail->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	} else {
		for (int i = 0; i < self->else_body->body->Length; i++) {
			il_stmt* stmt = (il_stmt*)AtVector(self->else_body->body, i);
			GenerateILStmt(stmt, env, cctx);
		}
		tail->Cursor = AddNOPOpcodeBuf(env->Bytecode);
	}
	env->Symboles->ScopeDepth--;
}

void LoadILIf(il_stmt_if * self, Enviroment* env, CallContext* cctx) {
	env->Symboles->ScopeDepth++;
	LoadILFactor(self->condition, env, cctx);
	for(int i=0; i<self->body->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->body, i);
		LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	for(int i=0; i<self->elif_list->Length; i++) {
		il_stmt_elif* e = (il_stmt_elif*)AtVector(self->elif_list, i);
		LoadILFactor(e->condition, env, cctx);
		for(int j=0; j<e->body->Length; j++) {
			il_stmt* st = (il_stmt*)AtVector(e->body, j);
			LoadILStmt(st, env, cctx);
			BC_ERROR();
		}
		BC_ERROR();
	}
	for(int i=0; i<self->else_body->body->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->else_body->body, i);
		LoadILStmt(e, env, cctx);
		BC_ERROR();
	}
	//条件が bool を返さない
	BC_ERROR();
	check_condition_type(self->condition, env, cctx);
	for(int i=0; i<self->elif_list->Length; i++) {
		il_stmt_elif* elif = AtVector(self->elif_list, i);
		check_condition_type(elif->condition, env, cctx);
		BC_ERROR();
	}
	env->Symboles->ScopeDepth--;
}

void DeleteILIf(il_stmt_if * self) {
	DeleteVector(self->elif_list, DeleteILElifList_impl);
	DeleteILElse(self->else_body);
	DeleteVector(self->body, DeleteILIf_stmt);
	DeleteILFactor(self->condition);
	MEM_FREE(self);
}

void DeleteILElif(il_stmt_elif * self) {
	DeleteILFactor(self->condition);
	DeleteVector(self->body, DeleteILIf_stmt);
	MEM_FREE(self);
}

void DeleteILElifList(Vector * self) {
	DeleteVector(self, DeleteILElifList_impl);
}

void DeleteILElse(il_stmt_else * self) {
	DeleteVector(self->body, DeleteILIf_stmt);
	MEM_FREE(self);
}

//private
static void DeleteILElifList_impl(VectorItem item) {
	il_stmt_elif* el = (il_stmt_elif*)item;
	DeleteILElif(el);
}

static void DeleteILIf_stmt(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}

static void check_condition_type(il_factor* fact, Enviroment* env, CallContext* cctx) {
	GenericType* cond_T = EvalILFactor(fact, env, cctx);
	if(cond_T->CoreType != TYPE_BOOL) {
		char* condstr = ILFactorToString(fact, env);
		ThrowBCError(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}