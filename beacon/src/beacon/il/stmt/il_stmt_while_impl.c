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

il_stmt * il_stmt_wrap_while(il_stmt_while * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_WHILE_T);
	ret->u.while_ = self;
	return ret;
}

il_stmt_while * il_stmt_while_new() {
	il_stmt_while* ret = (il_stmt_while*)MEM_MALLOC(sizeof(il_stmt_while));
	ret->statement_list = NewVector();
	ret->condition = NULL;
	return ret;
}

void il_stmt_while_generate(il_stmt_while * self, enviroment * env, call_context* cctx) {
	env->sym_table->scope_depth++;
	int prev = AddNOPOpcodeBuf(env->buf);
	label* prevLab = AddLabelOpcodeBuf(env->buf, prev);
	label* nextLab = AddLabelOpcodeBuf(env->buf, -1);
	PushVector(cctx->control.while_start, prevLab);
	PushVector(cctx->control.while_end, nextLab);
	//条件を満たさないなら nextLab へ
	il_factor_generate(self->condition, env, cctx);
	AddOpcodeBuf(env->buf, OP_GOTO_if_false);
	AddOpcodeBuf(env->buf, nextLab);
	//全てのステートメントを実行
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		il_stmt_generate(e, env, cctx);
	}
	//prevLab へ行って再判定
	AddOpcodeBuf(env->buf, OP_GOTO);
	AddOpcodeBuf(env->buf, prevLab);
	PopVector(cctx->control.while_start);
	PopVector(cctx->control.while_end);
	int next = AddNOPOpcodeBuf(env->buf);
	nextLab->cursor = next;
	env->sym_table->scope_depth--;
}

void il_stmt_while_delete(il_stmt_while * self) {
	DeleteVector(self->statement_list, il_stmt_while_stmt_delete);
	il_factor_delete(self->condition);
	MEM_FREE(self);
}

void il_stmt_while_load(il_stmt_while* self, struct enviroment* env, call_context* cctx) {
	env->sym_table->scope_depth++;
	il_factor_load(self->condition, env, cctx);
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->statement_list, i);
		il_stmt_load(e, env, cctx);
	}
	check_condition_type(self->condition, env, cctx);
	env->sym_table->scope_depth--;
}

//private
static void il_stmt_while_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx) {
	generic_type* cond_T = il_factor_eval(fact, env, cctx);
	if(cond_T->core_type != TYPE_BOOL) {
		char* condstr = il_factor_tostr(fact, env);
		ThrowBCError(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}
