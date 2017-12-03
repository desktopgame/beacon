#include "ast.h"
#include "../util/text.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
//proto
static void ast_print_indent(int depth);
static void ast_print_tree_impl(ast* self, int depth);
static void ast_delete_impl(ast* self);

ast * ast_new(ast_tag tag) {
	ast* ret = (ast*)malloc(sizeof(ast));
	ret->tag = tag;
	ret->childCount = 0;
	ret->children = NULL;
	return ret;
}

ast * ast_push(ast * self, ast * child) {
	assert(self != NULL);
	assert(child != NULL);
	if (self->children == NULL) {
		self->children = list_new();
	}
	list_add(self->children, child);
	self->childCount++;
	return self;
}

ast* ast_at(ast * self, int index) {
	assert(self != NULL);
	assert(index >= 0 && index < self->childCount);
	return (ast*)list_at(self->children, index);
}

void ast_print_tree(ast * self) {
	ast_print_tree_impl(self, 0);
}

void ast_print(ast* self) {
	switch (self->tag) {
		case ast_add:
			printf("+");
			break;
		case ast_sub:
			printf("-");
			break;
		case ast_mul:
			printf("*");
			break;
		case ast_div:
			printf("/");
			break;
		case ast_mod:
			printf("%");
			break;
		case ast_bit_or:
			printf("|");
			break;
		case ast_logic_or:
			printf("||");
			break;
		case ast_bit_and:
			printf("&");
			break;
		case ast_logic_and:
			printf("&&");
			break;
		case ast_assign:
			printf("=");
			break;
		case ast_add_assign:
			printf("+=");
			break;
		case ast_sub_assign:
			printf("-=");
			break;
		case ast_mul_assign:
			printf("*=");
			break;
		case ast_div_assign:
			printf("/=");
			break;
		case ast_mod_assign:
			printf("%=");
			break;
		case ast_int:
			printf("int(%d)", self->u.int_value);
			break;
		case ast_double:
			printf("double(%f)", self->u.double_value);
			break;
		default:
			printf("not implemented");
			break;
	}
}

void ast_delete(ast * self) {
	ast_delete_impl(self);
}

//private
static void ast_print_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void ast_print_tree_impl(ast* self, int depth) {
	ast_print_indent(depth);
	ast_print(self);
	text_putline();
	for (int i = 0; i < self->childCount; i++) {
		ast_print_tree_impl(ast_at(self, i), depth + 1);
	}
}

static void ast_delete_impl(ast* self) {
	for (int i = 0; i < self->childCount; i++) {
		ast_delete_impl(list_at(self->children, i));
	}
	list_delete(self->children, list_deleter_null);
	free(self);
}