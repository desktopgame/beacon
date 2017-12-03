#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
//proto
static void ast_print_indent(int depth);
static void ast_print_tree_impl(ast* self, int depth);
static void ast_delete_impl(ast* self);

void ast_compile_entry(ast * self) {
	parser* p = parser_top();
	ast_push(p->root, self);
}

ast * ast_new(ast_tag tag) {
	ast* ret = (ast*)malloc(sizeof(ast));
	ret->tag = tag;
	ret->childCount = 0;
	ret->children = NULL;
	return ret;
}

ast * ast_new_blank() {
	return ast_new(ast_blank);
}

ast * ast_new_int(int i) {
	ast* ret = ast_new(ast_int);
	ret->u.int_value = i;
	return ret;
}

ast * ast_new_double(double d) {
	ast* ret = ast_new(ast_double);
	ret->u.double_value = d;
	return ret;
}

ast * ast_new_pre_inc(ast * a) {
	ast* ret = ast_new(ast_pre_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_pre_dec(ast * a) {
	ast* ret = ast_new(ast_pre_dec);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_inc(ast * a) {
	ast* ret = ast_new(ast_post_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_dec(ast * a) {
	ast* ret = ast_new(ast_post_dec);
	ast_push(ret, a);
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
#define p(str) printf(str); break
	switch (self->tag) {
		case ast_root: p("root");
		case ast_add:  p("+");
		case ast_sub:  p("-");
		case ast_mul: p("*");
		case ast_div: p("/");
		case ast_mod: p("%");
		case ast_bit_or: p("|");
		case ast_logic_or: p("||");
		case ast_bit_and: p("&");
		case ast_logic_and: p("&&");
		case ast_assign: p("=");
		case ast_add_assign: p("+=");
		case ast_sub_assign: p("-=");
		case ast_mul_assign: p("*=");
		case ast_div_assign: p("/=");
		case ast_mod_assign: p("%=");
		case ast_equal: p("==");
		case ast_notequal: p("!=");
		case ast_gt: p(">");
		case ast_ge: p(">=");
		case ast_lt: p("<");
		case ast_le: p("<=");
		case ast_pre_inc:
		case ast_post_inc:
			p("++");
		case ast_pre_dec:
		case ast_post_dec:
			p("--");
		case ast_int:
			printf("int(%d)", self->u.int_value);
			break;
		case ast_double:
			printf("double(%f)", self->u.double_value);
			break;
		default: p("not implemented");
	}
#undef p
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