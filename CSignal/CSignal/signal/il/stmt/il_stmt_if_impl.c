#include "il_stmt_if_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/opcode_buf.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void il_stmt_elif_list_delete_impl(vector_item item);
static void il_stmt_if_delete_stmt(vector_item item);

il_stmt * il_stmt_wrap_if(il_stmt_if * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_if;
	ret->u.if_ = self;
	return ret;
}

il_stmt_if * il_stmt_if_new() {
	il_stmt_if* ret = (il_stmt_if*)MEM_MALLOC(sizeof(il_stmt_if));
	ret->condition = NULL;
	ret->elif_list = vector_new();
	ret->else_body = il_stmt_else_new();
	ret->body = vector_new();
	return ret;
}

il_stmt_elif * il_stmt_elif_new() {
	il_stmt_elif* ret = (il_stmt_elif*)MEM_MALLOC(sizeof(il_stmt_elif));
	ret->condition = NULL;
	ret->body = vector_new();
	return ret;
}

vector * il_stmt_elif_list_new() {
	return vector_new();
}

il_stmt_else * il_stmt_else_new() {
	il_stmt_else* ret = (il_stmt_else*)MEM_MALLOC(sizeof(il_stmt_else));
	ret->body = vector_new();
	return ret;
}

void il_stmt_elif_list_push(vector * self, il_stmt_elif * child) {
//	list_add(self, child);
	vector_push(self, child);
}

void il_stmt_if_dump(il_stmt_if * self, int depth) {
	text_putindent(depth);
	printf("if");
	text_putline();
	il_factor_dump(self->condition, depth + 1);
	//ステートメントの一覧をダンプ
	for (int i = 0; i < self->body->length; i++) {
		vector_item e = vector_at(self->body, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
	//エルスイフの一覧をダンプ
	for (int i = 0; i < self->elif_list->length; i++) {
		vector_item e = vector_at(self->elif_list, i);
		il_stmt_elif* elif = (il_stmt_elif*)e;
		text_putindent(depth);
		printf("elif");
		text_putline();
		il_factor_dump(elif->condition, depth + 1);
		for (int i = 0; i < elif->body->length; i++) {
			vector_item e = vector_at(elif->body, i);
			il_stmt* s = (il_stmt*)e;
			il_stmt_dump(s, depth + 1);
		}
	}
	
	text_putindent(depth + 1);
	printf("else");
	text_putline();
	//ステートメントの一覧をダンプ
	for (int i = 0; i < self->else_body->body->length; i++) {
		vector_item e = vector_at(self->else_body->body, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
	text_putline();
}

void il_stmt_if_generate(il_stmt_if * self, enviroment* env) {
}

void il_stmt_if_load(il_stmt_if * self, struct enviroment* env, il_ehandler * eh) {
}

void il_stmt_if_delete(il_stmt_if * self) {
//	il_stmt_elif_list_delete(self->elif_list);
	vector_delete(self->elif_list, il_stmt_elif_list_delete_impl);
	il_stmt_else_delete(self->else_body);
	//vector_delete(self->else_body, il_stmt_if_delete_stmt);
	vector_delete(self->body, il_stmt_if_delete_stmt);
	il_factor_delete(self->condition);
	MEM_FREE(self);
}

void il_stmt_elif_delete(il_stmt_elif * self) {
	il_factor_delete(self->condition);
	vector_delete(self->body, il_stmt_if_delete_stmt);
	//il_stmt_list_delete(self->body);
	MEM_FREE(self);
}

void il_stmt_elif_list_delete(vector * self) {
	vector_delete(self, il_stmt_elif_list_delete_impl);
}

void il_stmt_else_delete(il_stmt_else * self) {
	vector_delete(self->body, il_stmt_if_delete_stmt);
	MEM_FREE(self);
}

//private
static void il_stmt_elif_list_delete_impl(vector_item item) {
	il_stmt_elif* el = (il_stmt_elif*)item;
	il_stmt_elif_delete(el);
}

static void il_stmt_if_delete_stmt(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}