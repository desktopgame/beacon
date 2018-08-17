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
static modifier_type ast_cast_to_modifierImpl(ast * self, bool* error);
static void ast_delete_self(vector_item item);

void ast_compile_entry(ast * self) {
	parser* p = parser_current();
	ast_push(p->root, self);
}

ast * ast_malloc(ast_tag tag, const char* filename, int lineno) {
	ast* ret = (ast*)mem_malloc(sizeof(ast), filename, lineno);
	assert(ret != NULL);
	ret->tag = tag;
	ret->vchildren = NULL;
	//行番号を取得
	parser* p = parser_current();
	if (p != NULL) {
		ret->lineno = p->lineno;
		assert(p->lineno >= 0);
		vector_push(p->lineno_vec, p->lineno);
	} else {
		ret->lineno = -1;
	}
	return ret;
}

ast * ast_new_namespace_path(string_view namev) {
	ast* ret = ast_new(ast_namespace_path);
	ret->u.stringv_value = namev;
	return ret;
}

ast * ast_new_namespace_path_list(ast * aforward, string_view namev) {
	ast* ret = ast_new(ast_namespace_path_list);
	ast_push(ret, aforward);
	ast_push(ret, ast_new_namespace_path(namev));
	return ret;
}

ast * ast_new_import_path(ast* astr) {
	ast* ret = ast_new(ast_import_path);
	ret->u.stringv_value = astr->u.stringv_value;
	astr->u.stringv_value = 0;
	MEM_FREE(astr);
	return ret;
}

ast * ast_new_import_decl(ast * aimport_path) {
	ast* ret = ast_new(ast_import_decl);
	ast_push(ret, aimport_path);
	return ret;
}

ast* ast_new_import_decl_list(ast* aimport, ast* aimport_list) {
	ast* ret = ast_new(ast_import_decl_list);
	ast_push(ret, aimport);
	ast_push(ret, aimport_list);
	return ret;
}

ast * ast_new_scope(ast * astmt_list) {
	ast* ret = ast_new(ast_scope);
	ast_push(ret, astmt_list);
	return ret;
}

ast * ast_new_scope_empty() {
	return ast_new_scope(ast_new_blank());
}

ast * ast_new_blank() {
	return ast_new(ast_blank);
}

ast * ast_new_identifier(string_view strv) {
	ast* ret = ast_new(ast_identifier);
	ret->u.stringv_value = strv;
	return ret;
}

ast * ast_new_identifier_list(string_view strv, ast * aident_list) {
	ast* ret = ast_new(ast_identifier_list);
	ast_push(ret, aident_list);
	ast_push(ret, ast_new_identifier(strv));
	return ret;
}

ast * ast_new_proc(ast * aexpr) {
	ast* ret = ast_new(ast_proc);
	ast_push(ret, aexpr);
	return ret;
}

ast * ast_push(ast * self, ast * achild) {
	assert(self != NULL);
	assert(achild != NULL);
	if (self->vchildren == NULL) {
		self->vchildren = vector_new();
	}
	vector_push(self->vchildren, achild);
	//行番号を補正
	parser* p = parser_current();
	if (p != NULL) {
		if (!vector_empty(p->lineno_vec)) {
			int lineno = (int)vector_pop(p->lineno_vec);
			assert(lineno >= 0);
			self->lineno = lineno;
		}
	}
	return self;
}

ast* ast_at(ast * self, int index) {
	assert(self != NULL);
	return (ast*)vector_at(self->vchildren, index);
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
		case ast_mod: p("%%");
		case ast_bit_or: p("|");
		case ast_logic_or: p("||");
		case ast_bit_and: p("&");
		case ast_logic_and: p("&&");
		case ast_assign: p("=");
		case ast_add_assign: p("+=");
		case ast_sub_assign: p("-=");
		case ast_mul_assign: p("*=");
		case ast_div_assign: p("/=");
		case ast_mod_assign: p("%%=");
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
		case ast_lambda: p("lambda");
		case ast_op_call: p("call");
		case ast_stmt_variable_decl: p("variable-decl");
		case ast_stmt_variable_init: p("variable-init");
		case ast_typename:
			printf("typename");
			break;
		case ast_identifier:
			printf("identifier(%s)", string_pool_ref2str(self->u.stringv_value));
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
			printf("string(%s)", string_pool_ref2str(self->u.stringv_value));
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
			printf("namespace_path(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_namespace_path_list:
			printf("namespace_path list");
			break;
		case ast_class_decl_unit:
			printf("class decl_unit");
			break;
		case ast_variable:
		{
			ast* a = ast_first(self);
			printf("variable %s", string_pool_ref2str(a->u.stringv_value));
			break;
		}
		case ast_static_invoke: p("static invoke");
		case ast_fqcn: p("fqcn");
		case ast_fqcn_part_list: p("fqcn part-list");
		case ast_fqcn_part: 
			printf("fqcn part %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_fqcn_class_name: 
			printf("fqcn class-name %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_invoke: p("invoke");
		case ast_call: p("call");
		case ast_proc: p("process");
		case ast_argument_list: p("argument-list");
		case ast_argument: p("argument");
		case ast_new_instance: p("new-instance");
		case ast_import_decl: p("import");
		case ast_import_path:
			printf("%s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_abstract_class_decl:
			printf("abstract class");
			break;
		case ast_class_decl:
			printf("class");
			break;
		case ast_interface_decl:
			printf("interface(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_class_super:
			printf("super_class(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_access_member_tree: p("access member_tree");
		case ast_access_member_list: p("access member_list");
		case ast_access_level: p("access");
		case ast_modifier: p("modifier");
		case ast_constructor_decl: p("constructor");
		case ast_constructor_chain: p("constructor chain");
		case ast_constructor_chain_this: p("this");
		case ast_constructor_chain_super: p("super");
		case ast_member_decl: p("member_decl");
		case ast_member_decl_list: p("member_decl_list");
		case ast_field_decl: p("field decl");
		case ast_field_type_name:
			printf("type_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_field_access_name:
			printf("access_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_prop_decl:
			printf("prop %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_prop_set:
			printf("prop-set");
			break;
		case ast_prop_get:
			printf("prop-get");
			break;
		case ast_method_decl: p("method decl");
		case ast_method_name:
			printf("method_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameter_list: p("parameter-list");
		case ast_parameter: p("parameter");
		case ast_parameter_type_name:
			printf("parameter_type_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameter_access_name:
			printf("parameter_access_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_method_return_name:
			printf("method_return_name(%s)", string_pool_ref2str(self->u.stringv_value));
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
		case ast_subscript_access: p("[]");
		case ast_blank:
			printf("blank");
			break;
		case ast_function_decl: p("function decl");
		case ast_function_name: p("function name");
		case ast_function_return_name: p("function return name");
		case ast_while: p("while");
		case ast_true: p("true");
		case ast_false: p("false");
		case ast_break: p("break");
		case ast_continue: p("continue");
		case ast_enum_decl:
			printf("enum(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_identifier_list: p("ident list");
		case ast_inferenced_type_init: p("var init");
		case ast_stmt_throw: p("throw");
		case ast_stmt_try: p("try");
		case ast_stmt_catch_list: p("catch list");
		case ast_stmt_catch: p("catch");
		case ast_yield_return: p("yield return");
		case ast_yield_break: p("yield break");
		case ast_null: p("null");
		case ast_as: p("as");
		case ast_type_parameter: 
			printf("type parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_in_parameter:
			printf("type in parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_out_parameter:
			printf("type out parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameterized_typename:
			printf("typename(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_parameter_list: p("type parameter list");
		case ast_type_parameter_rule_list: p("type parameter rule list");
		case ast_stmt_assert: p("assert");
		case ast_typename_list: p("typename list");
		default: 
			p("not implemented");
	}
#undef p
	printf("<%d>", self->lineno);
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
	return self->tag == ast_access_level;
}

bool ast_is_modifier(ast * self) {
	return self->tag == ast_modifier;
}

bool ast_is_stmt(ast* self) {
	switch(self->tag) {
		case ast_stmt:
		case ast_stmt_list:
		case ast_stmt_variable_decl:
		case ast_stmt_variable_init:
		case ast_inferenced_type_init:
		case ast_if:
		case ast_if_elif_list:
		case ast_if_elif_list_else:
		case ast_elif:
		case ast_else:
		case ast_while:
		case ast_continue:
		case ast_break:
		case ast_proc:
		case ast_stmt_assert:
		case ast_stmt_try:
		case ast_stmt_catch:
		case ast_stmt_catch_list:
		case ast_stmt_defer:
			return true;
	}
	return false;
}

access_level ast_cast_to_access(ast * self) {
	assert(ast_is_access(self));
	return self->u.access_value;
}

modifier_type ast_cast_to_modifier(ast * self, bool* error) {
	(*error) = false;
	if(self->tag == ast_modifier_list) {
		return ast_cast_to_modifierImpl(self, error);
	}
	assert(ast_is_modifier(self));
	return self->u.modifier_value;
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
	io_println();
	if(self->vchildren != NULL) {
		for (int i = 0; i < self->vchildren->length; i++) {
			ast_print_tree_impl(ast_at(self, i), depth + 1);
		}
	}
}

static void ast_delete_impl(ast* self) {
	ast_tag tag =self->tag;
	vector_delete(self->vchildren, ast_delete_self);
	self->vchildren = NULL;
	MEM_FREE(self);
}

static modifier_type ast_cast_to_modifierImpl(ast * self, bool* error) {
	int ret = -1;
	for(int i=0; i<self->vchildren->length; i++) {
		if((*error)) {
			break;
		}
		//フラグを合体させる
		if(ret == -1) {
			ret = ast_cast_to_modifier(ast_at(self, i), error);
		} else {
			//追加の属性がすでに含まれているかどうか
			modifier_type add = ast_cast_to_modifier(ast_at(self, i), error);
			if((ret & add) > 0) {
				(*error) = true;
			}
			ret |= add;
		}
	}
	modifier_type mt = (modifier_type)ret;
	return mt;
}

static void ast_delete_self(vector_item item) {
	ast* e = (ast*)item;
	ast_delete(e);
}