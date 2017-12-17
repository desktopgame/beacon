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
static bool ast_has_str(ast* self);

void ast_compile_entry(ast * self) {
	parser* p = parser_top();
	if (p->fail) {
		free(self);
		return;
	}
	ast_push(p->root, self);
}

ast * ast_new(ast_tag tag) {
	ast* ret = (ast*)malloc(sizeof(ast));
	assert(ret != NULL);
	ret->tag = tag;
	ret->childCount = 0;
	ret->children = NULL;
	return ret;
}

ast * ast_new_namespace_path(char * name) {
	ast* ret = ast_new(ast_namespace_path);
	ret->u.string_value = name;
	return ret;
}

ast * ast_new_namespace_path_list(ast * forward, char * name) {
	ast* ret = ast_new(ast_namespace_path_list);
	ast_push(ret, forward);
	ast_push(ret, ast_new_namespace_path(name));
	return ret;
}

ast * ast_new_import_path(ast* str) {
	ast* ret = ast_new(ast_import_path);
	ret->u.string_value = str->u.string_value;
	str->u.string_value = NULL;
	free(str);
	return ret;
}

ast * ast_new_import_decl(ast * import_path) {
	ast* ret = ast_new(ast_import_decl);
	ast_push(ret, import_path);
	return ret;
}

ast * ast_new_scope(ast * stmt_list) {
	ast* ret = ast_new(ast_scope);
	ast_push(ret, stmt_list);
	return ret;
}

ast * ast_new_scope_empty() {
	return ast_new_scope(ast_new_blank());
}

ast * ast_new_blank() {
	return ast_new(ast_blank);
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

ast * ast_new_typename(char * str) {
	ast* ret = ast_new(ast_typename);
	ret->u.string_value = str;
	return ret;
}

ast * ast_new_identifier(char * str) {
	ast* ret = ast_new(ast_identifier);
	ret->u.string_value = str;
	return ret;
}

ast * ast_new_variable(const char * name) {
	ast* ret = ast_new(ast_variable);
	ret->u.string_value = name;
	return ret;
}

ast * ast_new_call(const char * name, ast * argument_list) {
	ast* ret = ast_new(ast_call);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_invoke(ast * receiver, const char* name, ast * argument_list) {
	ast* ret = ast_new(ast_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, receiver);
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_proc(ast * expr) {
	ast* ret = ast_new(ast_proc);
	ast_push(ret, expr);
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

ast * ast_first(ast * self) {
	return ast_at(self, 0);
}

ast * ast_second(ast * self) {
	return ast_at(self, 1);
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
		case ast_variable_decl: p("variable-decl");
		case ast_typename:
			printf("typename(%s)", self->u.string_value);
			break;
		case ast_identifier:
			printf("identifier(%s)", self->u.string_value);
			break;
		case ast_int:
			printf("int(%d)", self->u.int_value);
			break;
		case ast_double:
			printf("double(%f)", self->u.double_value);
			break;
		case ast_char:
			printf("char(%c)", self->u.char_value);
			break;
		case ast_string:
			printf("string(%s)", self->u.string_value);
			break;
		case ast_namespace_decl:
			printf("namespace decl");
			break;
		case ast_namespace_member_decl_list:
			printf("namepsace member decl");
			break;
		case ast_namespace_path:
			printf("namespace_path(%s)", self->u.string_value);
			break;
		case ast_namespace_path_list:
			printf("namespace_path list");
			break;
		case ast_class_decl_unit:
			printf("class decl_unit");
			break;
		case ast_variable:
			printf("variable %s", self->u.string_value);
			break;
		case ast_invoke: p("invoke");
		case ast_call: p("call");
		case ast_proc: p("process");
		case ast_argument_list: p("argument-list");
		case ast_argument: p("argument");
		//case ast_class_decl_list:
		//	printf("class decl_list");
		//	break;
		case ast_import_decl: p("import");
		case ast_import_path:
			printf("%s", self->u.string_value);
			break;
		case ast_class_decl:
			printf("class(%s)", self->u.string_value);
			break;
		case ast_class_super:
			printf("super_class(%s)", self->u.string_value);
			break;
		case ast_member_decl: p("member_decl");
		case ast_member_decl_list: p("member_decl_list");
		case ast_field_decl: p("field decl");
		case ast_field_type_name:
			printf("type_name(%s)", self->u.string_value);
			break;
		case ast_field_access_name:
			printf("access_name(%s)", self->u.string_value);
			break;
		case ast_func_decl: p("func decl");
		case ast_func_name:
			printf("func_name(%s)", self->u.string_value);
			break;
		case ast_parameter: p("parameter");
		case ast_parameter_type_name:
			printf("parameter_type_name(%s)", self->u.string_value);
			break;
		case ast_parameter_access_name:
			printf("parameter_access_name(%s)", self->u.string_value);
			break;
		case ast_func_return_name:
			printf("func_return_name(%s)", self->u.string_value);
			break;
		case ast_scope: p("scope");
		case ast_stmt: p("stmt");
		case ast_stmt_list: p("stmt list");
		case ast_if: p("if");
		case ast_if_else: p("if else");
		case ast_if_elif_list: p("if elif_list");
		case ast_if_elif_list_else: p("if elif_list else");
		case ast_elif: p("elif");
		case ast_else: p("else");
		case ast_blank:
			printf("blank");
			break;
		default: 
			p("not implemented");
	}
#undef p
}

void ast_delete(ast * self) {
	ast_delete_impl(self);
}

bool ast_is_blank(ast * self) {
	return self == NULL || self->tag == ast_blank;
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
		ast_delete((ast*)list_at(self->children, i));
	}
	list_delete(self->children, list_deleter_null);
	ast_tag t = self->tag;
	if (ast_has_str(self)) {
		printf("free(%s)\n", self->u.string_value);
		free(self->u.string_value);
		self->u.string_value = NULL;
	}
	free(self);
}

static bool ast_has_str(ast* self) {
	ast_tag t = self->tag;
	return
		t == ast_typename ||
		t == ast_identifier ||
		t == ast_variable ||
		t == ast_string ||
		t == ast_import_path ||
		t == ast_namespace_path ||
		t == ast_field_type_name ||
		t == ast_field_access_name ||
		t == ast_func_name ||
		t == ast_func_return_name ||
		t == ast_parameter_type_name ||
		t == ast_parameter_access_name ||
		t == ast_class_decl ||
		t == ast_class_super;
}