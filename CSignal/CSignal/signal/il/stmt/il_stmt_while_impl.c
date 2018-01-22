#include "il_stmt_while_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include <stdio.h>

//proto
static void il_stmt_while_stmt_delete(vector_item item);

il_stmt * il_stmt_wrap_while(il_stmt_while * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_while;
	ret->u.while_ = self;
	return ret;
}

il_stmt_while * il_stmt_while_new() {
	il_stmt_while* ret = (il_stmt_while*)MEM_MALLOC(sizeof(il_stmt_while));
	ret->statement_list = vector_new();
	ret->condition = NULL;
	return ret;
}

void il_stmt_while_dump(il_stmt_while * self, int depth) {
	text_putindent(depth);
	printf("while");
	text_putline();
	il_factor_dump(self->condition, depth + 1);
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_stmt_while_generate(il_stmt_while * self, enviroment * env) {
	int prev = opcode_buf_nop(env->buf);
	label* prevLab = opcode_buf_label(env->buf, prev);
	label* nextLab = opcode_buf_label(env->buf, -1);
	vector_push(env->whileStart_vec, prevLab);
	vector_push(env->whileEnd_vec, nextLab);
	//条件を満たさないなら nextLab へ
	il_factor_generate(self->condition, env);
	opcode_buf_add(env->buf, op_goto_if_false);
	opcode_buf_add(env->buf, nextLab);
	//全てのステートメントを実行
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_generate(e, env);
	}
	//prevLab へ行って再判定
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, prevLab);

	int next = opcode_buf_nop(env->buf);
	nextLab->cursor = next;
	vector_pop(env->whileStart_vec);
	vector_pop(env->whileEnd_vec);
}

void il_stmt_while_delete(il_stmt_while * self) {
	vector_delete(self->statement_list, il_stmt_while_stmt_delete);
	il_factor_delete(self->condition);
	MEM_FREE(self);
}
//private
static void il_stmt_while_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}
