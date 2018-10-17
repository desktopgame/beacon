#include "il_stmt_while_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include <stdio.h>
#include "../call_context.h"

//proto
static void il_stmt_while_stmt_delete(VectorItem item);
static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx);

il_stmt * WrapILWhile(il_stmt_while * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_WHILE_T);
	ret->u.while_ = self;
	return ret;
}

il_stmt_while * NewILWhile() {
	il_stmt_while* ret = (il_stmt_while*)MEM_MALLOC(sizeof(il_stmt_while));
	ret->statement_list = NewVector();
	ret->condition = NULL;
	return ret;
}

void GenerateILWhile(il_stmt_while * self, enviroment * env, call_context* cctx) {
	env->sym_table->scope_depth++;
	int prev = AddNOPOpcodeBuf(env->buf);
	Label* prevLab = AddLabelOpcodeBuf(env->buf, prev);
	Label* nextLab = AddLabelOpcodeBuf(env->buf, -1);
	PushVector(cctx->control.while_start, prevLab);
	PushVector(cctx->control.while_end, nextLab);
	//条件を満たさないなら nextLab へ
	GenerateILFactor(self->condition, env, cctx);
	AddOpcodeBuf(env->buf, OP_GOTO_if_false);
	AddOpcodeBuf(env->buf, nextLab);
	//全てのステートメントを実行
	for (int i = 0; i < self->statement_list->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		GenerateILStmt(e, env, cctx);
	}
	//prevLab へ行って再判定
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, prevLab);
	PopVector(cctx->control.while_start);
	PopVector(cctx->control.while_end);
	int next = AddNOPOpcodeBuf(env->buf);
	nextLab->Cursor = next;
	env->sym_table->scope_depth--;
}

void DeleteILWhile(il_stmt_while * self) {
	DeleteVector(self->statement_list, il_stmt_while_stmt_delete);
	DeleteILFactor(self->condition);
	MEM_FREE(self);
}

void LoadILWhile(il_stmt_while* self, struct enviroment* env, call_context* cctx) {
	env->sym_table->scope_depth++;
	LoadILFactor(self->condition, env, cctx);
	for(int i=0; i<self->statement_list->Length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		LoadILStmt(e, env, cctx);
	}
	check_condition_type(self->condition, env, cctx);
	env->sym_table->scope_depth--;
}

//private
static void il_stmt_while_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}

static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx) {
	generic_type* cond_T = EvalILFactor(fact, env, cctx);
	if(cond_T->core_type != TYPE_BOOL) {
		char* condstr = ILFactorToString(fact, env);
		ThrowBCError(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}
