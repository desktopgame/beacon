#include "ast.h"
#include "../util/text.h"
#include "../parse/parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
//proto
static void ast_print_indent(int depth);
static void ast_print_tree_impl(ast* self, int depth);
static void ast_delete_impl(ast* self);
static void ast_list_deleter(list_item item);
static bool ast_has_str(ast* self);

void ast_compile_entry(ast * self) {
	parser* p = parser_top();
	if (p->fail) {
		MEM_FREE(self);
		return;
	}
	ast_push(p->root, self);
}

ast * ast_new(ast_tag tag) {
	ast* ret = (ast*)MEM_MALLOC(sizeof(ast));
	assert(ret != NULL);
	ret->tag = tag;
	ret->childCount = 0;
	ret->children = NULL;
	return ret;
}

ast * ast_new_true() {
	return ast_new(ast_true);
}

ast * ast_new_false() {
	return ast_new(ast_false);
}

ast * ast_new_namespace_path(char * name) {
	ast* ret = ast_new(ast_namespace_path);
	ret->u.string_value = name;
	return ret;
}

ast * ast_new_cast(ast * atypename, ast * afact) {
	ast* ret = ast_new(ast_cast);
	ast_push(ret, atypename);
	ast_push(ret, afact);
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
	MEM_FREE(str);
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

ast * ast_new_static_invoke(ast * fqcn, const char * name, ast * argument_list) {
	ast* ret = ast_new(ast_static_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, fqcn);
	ast_push(ret, aname);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_proc(ast * expr) {
	ast* ret = ast_new(ast_proc);
	ast_push(ret, expr);
	return ret;
}

ast * ast_new_this() {
	return ast_new(ast_this);
}

ast * ast_new_super() {
	return ast_new(ast_super);
}

ast * ast_new_field_access(ast * afact, char * name) {
	ast* ret = ast_new(ast_field_access);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, afact);
	ast_push(ret, aname);
	return ret;
}

ast * ast_new_field_access_fqcn(ast * fqcn, char * name) {
//	assert(fqcn->tag != ast_fqcn_part_list);
	if (fqcn->tag == ast_fqcn_part ||
		fqcn->tag == ast_fqcn_class_name) {
		//この時点では point.a のようなアクセスを
		//インスタンス point のフィールド a へのアクセスなのか
		//クラス Point の静的フィールド a へのアクセスなのか判別出来ない
		//なので、とりあえずフィールドアクセスとして扱う
		//この判別は il_factor_field_access で行う。
		ast* ret = ast_new(ast_field_access);
		ast* avar = ast_new(ast_variable);
		ast* aname = ast_new(ast_identifier);
		avar->u.string_value = fqcn->u.string_value;
		aname->u.string_value = name;
		ast_push(ret, avar);
		ast_push(ret, aname);
		return ret;
	} else if (fqcn->tag == ast_fqcn || fqcn->tag == ast_fqcn_part_list) {
		//こっちの場合は静的フィールドへのアクセスと断定できる
		ast* ret = ast_new(ast_static_field_access);
		ast* aname = ast_new(ast_identifier);
		aname->u.string_value = name;
		ast_push(ret, fqcn);
		ast_push(ret, aname);
		return ret;
	}
	return NULL;
}

ast * ast_new_new_instance(ast * afqcn, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance);
	ast_push(ret, afqcn);
	ast_push(ret, argument_list);
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
		case ast_stmt_variable_decl: p("variable-decl");
		case ast_stmt_variable_init: p("variable-init");
		case ast_typename:
			printf("typename");
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
		case ast_this: p("this");
		case ast_super: p("super");
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
		case ast_static_invoke: p("static invoke");
		case ast_fqcn: p("fqcn");
		case ast_fqcn_part_list: p("fqcn part-list");
		case ast_fqcn_part: 
			printf("fqcn part %s", self->u.string_value);
			break;
		case ast_fqcn_class_name: 
			printf("fqcn class-name %s", self->u.string_value);
			break;
		case ast_invoke: p("invoke");
		case ast_call: p("call");
		case ast_proc: p("process");
		case ast_argument_list: p("argument-list");
		case ast_argument: p("argument");
		case ast_new_instance: p("new-instance");
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
		case ast_interface_decl:
			printf("interface(%s)", self->u.string_value);
			break;
		case ast_class_super:
			printf("super_class(%s)", self->u.string_value);
			break;
		case ast_access_member_tree: p("access member_tree");
		case ast_access_member_list: p("access member_list");
		case ast_access_public: p("public");
		case ast_access_private: p("private");
		case ast_access_protected: p("protected");
		case ast_modifier_none: p("none");
		case ast_modifier_static: p("static");
		case ast_modifier_native: p("native");
		case ast_modifier_static_native: p("static | native");
		case ast_constructor_decl: p("constructor");
		case ast_constructor_chain: p("constructor chain");
		case ast_constructor_chain_this: p("this");
		case ast_constructor_chain_super: p("super");
		case ast_member_decl: p("member_decl");
		case ast_member_decl_list: p("member_decl_list");
		case ast_field_decl: p("field decl");
		case ast_field_type_name:
			printf("type_name(%s)", self->u.string_value);
			break;
		case ast_field_access_name:
			printf("access_name(%s)", self->u.string_value);
			break;
		case ast_method_decl: p("method decl");
		case ast_method_name:
			printf("method_name(%s)", self->u.string_value);
			break;
		case ast_parameter_list: p("parameter-list");
		case ast_parameter: p("parameter");
		case ast_parameter_type_name:
			printf("parameter_type_name(%s)", self->u.string_value);
			break;
		case ast_parameter_access_name:
			printf("parameter_access_name(%s)", self->u.string_value);
			break;
		case ast_method_return_name:
			printf("method_return_name(%s)", self->u.string_value);
			break;
		case ast_field_access: p("field-access");
		case ast_static_field_access: p("static-field-access");
		case ast_scope: p("scope");
		case ast_stmt: p("stmt");
		case ast_stmt_list: p("stmt list");
		case ast_if: p("if");
		case ast_if_else: p("if else");
		case ast_if_elif_list: p("if elif_list");
		case ast_if_elif_list_else: p("if elif_list else");
		case ast_elif: p("elif");
		case ast_else: p("else");
		case ast_return: p("return");
		case ast_cast: p("cast");
		case ast_blank:
			printf("blank");
			break;
		case ast_function_decl: p("function decl");
		case ast_function_name: p("function name");
		case ast_function_return_name: p("function return name");
		case ast_while: p("while");
		case ast_true: p("true");
		case ast_false: p("false");
		default: 
			p("not implemented");
	}
#undef p
}

void ast_delete(ast * self) {
	if (self == NULL) {
		return;
	}
	ast_delete_impl(self);
}

bool ast_is_blank(ast * self) {
	return self == NULL || self->tag == ast_blank;
}

bool ast_is_access(ast * self) {
	return self->tag == ast_access_public ||
		self->tag == ast_access_private ||
		self->tag == ast_access_protected;
}

bool ast_is_modifier(ast * self) {
	return self->tag == ast_modifier_static ||
		self->tag == ast_modifier_native ||
		self->tag == ast_modifier_none ||
		self->tag == ast_modifier_static_native;
}

access_level ast_cast_to_access(ast * self) {
	assert(ast_is_access(self));
	switch (self->tag) {
		case ast_access_public:
			return access_public;

		case ast_access_private:
			return access_private;

		case ast_access_protected:
			return access_protected;
		default:
			break;
	}
	return access_public;
}

modifier_type ast_cast_to_modifier(ast * self) {
	assert(ast_is_modifier(self));
	switch (self->tag) {
		case ast_modifier_none:
			return modifier_none;

		case ast_modifier_static:
			return modifier_static;

		case ast_modifier_native:
			return modifier_native;

		case ast_modifier_static_native:
			return modifier_static | modifier_native;

		default:
			break;
	}
	return modifier_none;
}

constructor_chain_type ast_cast_to_chain_type(ast * self) {
	switch (self->tag) {
		case ast_constructor_chain_this:
			return chain_type_this;
		case ast_constructor_chain_super:
			return chain_type_super;
		default:
			break;
	}
	return chain_type_super;
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
	//*
	for (int i = 0; i < self->childCount; i++) {
		ast_delete((ast*)list_at(self->children, i));
	}
	list_delete(self->children, list_deleter_null);
	ast_tag t = self->tag;
	if (ast_has_str(self)) {
		//printf("free(%s)\n", self->u.string_value);
		char* temp = self->u.string_value;
		//self->u.string_value = NULL;
		//printf("_%s\n", temp);
		MEM_FREE(temp);
		//self->u.string_value = NULL;
	}
	MEM_FREE(self);
	//*/
	//list_delete(self->children, ast_list_deleter);
	//free(self);
}

static void ast_list_deleter(list_item item) {
	ast* self = (ast*)item;
	for (int i = 0; i < self->childCount; i++) {
		ast_delete(ast_at(self, i));
	}
	if (ast_has_str(self)) {
		//IL側で開放するように
		//printf("free(%s)\n", self->u.string_value);
		MEM_FREE(self->u.string_value);
		//self->u.string_value = NULL;
	}
	MEM_FREE(self);
}

static bool ast_has_str(ast* self) {
	ast_tag t = self->tag;
	return
		//t == ast_typename ||
		t == ast_identifier ||
		t == ast_variable ||
		t == ast_string ||
		t == ast_import_path ||
		t == ast_namespace_path ||
		t == ast_field_type_name ||
		t == ast_field_access_name ||
		t == ast_method_name ||
		t == ast_method_return_name ||
		t == ast_parameter_type_name ||
		t == ast_parameter_access_name ||
		t == ast_class_decl;
		//t == ast_class_super;
}