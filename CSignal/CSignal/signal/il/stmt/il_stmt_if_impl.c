#include "il_stmt_if_impl.h"
#include "../il_stmt_list.h"
#include "../../util/text.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void il_stmt_elif_list_dump_impl(il_stmt_elif_list* p, int depth);
static void il_stmt_elif_list_delete_impl(list_item item);

il_stmt * il_stmt_wrap_if(il_stmt_if * self) {
	il_stmt* ret = (il_stmt*)malloc(sizeof(il_stmt));
	ret->type = ilstmt_if;
	ret->u.if_ = self;
	return ret;
}

il_stmt_if * il_stmt_if_new() {
	il_stmt_if* ret = (il_stmt_if*)malloc(sizeof(il_stmt_if));
	ret->condition = NULL;
	ret->elif_list = il_stmt_elif_list_new();
	ret->else_body = il_stmt_else_new();
	ret->body = il_stmt_list_new();
	return ret;
}

il_stmt_elif * il_stmt_elif_new() {
	il_stmt_elif* ret = (il_stmt_elif*)malloc(sizeof(il_stmt_elif));
	ret->condition = NULL;
	ret->body = il_stmt_list_new();
	return ret;
}

il_stmt_elif_list * il_stmt_elif_list_new() {
	return list_new();
}

il_stmt_else * il_stmt_else_new() {
	il_stmt_else* ret = (il_stmt_else*)malloc(sizeof(il_stmt_else));
	ret->body = il_stmt_list_new();
	return ret;
}

void il_stmt_elif_list_push(il_stmt_elif_list * self, il_stmt_elif * child) {
	list_add(self, child);
}

void il_stmt_if_dump(il_stmt_if * self, int depth) {
	text_putindent(depth);
	printf("if");
	text_putline();
	il_factor_dump(self->condition, depth + 1);
	il_stmt_list_dump(self->body, depth + 1);
	il_stmt_elif_list_dump_impl(self->elif_list, depth + 1);

	text_putindent(depth + 1);
	printf("else");
	text_putline();
	il_stmt_list_dump(self->else_body->body, depth + 2);
	text_putline();
}

void il_stmt_if_delete(il_stmt_if * self) {
	il_stmt_elif_list_delete(self->elif_list);
	il_stmt_else_delete(self->else_body);
	il_stmt_list_delete(self->body);
	il_factor_delete(self->condition);
	free(self);
}

void il_stmt_elif_delete(il_stmt_elif * self) {
	il_factor_delete(self->condition);
	il_stmt_list_delete(self->body);
	free(self);
}

void il_stmt_elif_list_delete(il_stmt_elif_list * self) {
	list_delete(self, il_stmt_elif_list_delete_impl);
}

void il_stmt_else_delete(il_stmt_else * self) {
	il_stmt_list_delete(self->body);
	free(self);
}

//private
static void il_stmt_elif_list_dump_impl(il_stmt_elif_list* p, int depth) {
	if (p == NULL || p->item == NULL) {
		return;
	}
	text_putindent(depth);
	printf("elif");
	text_putline();
	il_stmt_elif* elif = (il_stmt_elif*)p->item;
	il_factor_dump(elif->condition, depth + 1);
	il_stmt_list_dump(elif->body, depth + 1);
}

static void il_stmt_elif_list_delete_impl(list_item item) {
	il_stmt_elif* el = (il_stmt_elif*)item;
	il_stmt_elif_delete(el);
}
