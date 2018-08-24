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
	ast* ret = ast_new(ast_namespace_path_T);
	ret->u.stringv_value = namev;
	return ret;
}

ast * ast_new_namespace_path_list(ast * aforward, string_view namev) {
	ast* ret = ast_new(ast_namespace_path_list_T);
	ast_push(ret, aforward);
	ast_push(ret, ast_new_namespace_path(namev));
	return ret;
}

ast * ast_new_import_path(ast* astr) {
	ast* ret = ast_new(ast_import_path_T);
	ret->u.stringv_value = astr->u.stringv_value;
	astr->u.stringv_value = 0;
	MEM_FREE(astr);
	return ret;
}

ast * ast_new_import_decl(ast * aimport_path) {
	ast* ret = ast_new(ast_import_decl_T);
	ast_push(ret, aimport_path);
	return ret;
}

ast* ast_new_import_decl_list(ast* aimport, ast* aimport_list) {
	ast* ret = ast_new(ast_import_decl_list_T);
	ast_push(ret, aimport);
	ast_push(ret, aimport_list);
	return ret;
}

ast * ast_new_scope(ast * astmt_list) {
	ast* ret = ast_new(ast_scope_T);
	ast_push(ret, astmt_list);
	return ret;
}

ast * ast_new_scope_empty() {
	return ast_new_scope(ast_new_blank());
}

ast * ast_new_blank() {
	return ast_new(ast_blank_T);
}

ast * ast_new_identifier(string_view strv) {
	ast* ret = ast_new(ast_identifier_T);
	ret->u.stringv_value = strv;
	return ret;
}

ast * ast_new_identifier_list(string_view strv, ast * aident_list) {
	ast* ret = ast_new(ast_identifier_list_T);
	ast_push(ret, aident_list);
	ast_push(ret, ast_new_identifier(strv));
	return ret;
}

ast * ast_new_proc(ast * aexpr) {
	ast* ret = ast_new(ast_proc_T);
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
		case ast_root_T: p("root");
		case ast_add_T:  p("+");
		case ast_sub_T:  p("-");
		case ast_mul_T: p("*");
		case ast_div_T: p("/");
		case ast_mod_T: p("%%");
		case ast_bit_or_T: p("|");
		case ast_logic_or_T: p("||");
		case ast_bit_and_T: p("&");
		case ast_logic_and_T: p("&&");
		case ast_as_Tsign_T: p("=");
		case ast_add_assign_T: p("+=");
		case ast_sub_assign_T: p("-=");
		case ast_mul_assign_T: p("*=");
		case ast_div_assign_T: p("/=");
		case ast_mod_assign_T: p("%%=");
		case ast_equal_T: p("==");
		case ast_not_Tequal_T: p("!=");
		case ast_gt_T: p(">");
		case ast_ge_T: p(">=");
		case ast_lt_T: p("<");
		case ast_le_T: p("<=");
		case ast_op_call_T: p("call");
		case ast_stmt_variable_decl_T: p("variable-decl");
		case ast_stmt_variable_init_T: p("variable-init");
		case ast_typename_T:
			printf("typename");
			break;
		case ast_identifier_T:
			printf("identifier(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_int_T:
			printf("int(%d)", self->u.int_value);
			break;
		case ast_double_T:
			printf("double(%f)", self->u.double_value);
			break;
		case ast_char_T:
			printf("char(%c)", self->u.char_value);
			break;
		case ast_string_T:
			printf("string(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_this_T: p("this");
		case ast_super_T: p("super");
		case ast_namespace_decl_T:
			printf("namespace decl");
			break;
		case ast_namespace_member_decl_list_T:
			printf("namepsace member decl");
			break;
		case ast_namespace_path_T:
			printf("namespace_path(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_namespace_path_list_T:
			printf("namespace_path list");
			break;
		case ast_class_decl_unit_T:
			printf("class decl_unit");
			break;
		case ast_variable_T:
		{
			printf("variable");
			break;
		}
		case ast_static_invoke_T: p("static invoke");
		case ast_fqcn_T: p("fqcn");
		case ast_fqcn_part_list_T: p("fqcn part-list");
		case ast_fqcn_part_T: 
			printf("fqcn part %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_fqcn_class_name_T: 
			printf("fqcn class-name %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_invoke_T: p("invoke");
		case ast_call_T: p("call");
		case ast_proc_T: p("process");
		case ast_argument_list_T: p("argument-list");
		case ast_argument_T: p("argument");
		case ast_new_instance_T: p("new-instance");
		case ast_import_decl_T: p("import");
		case ast_import_path_T:
			printf("%s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_abstract_class_decl_T:
			printf("abstract class");
			break;
		case ast_class_decl_T:
			printf("class");
			break;
		case ast_interface_decl:
			printf("interface");
			break;
		case ast_class_super_T:
			printf("super_class");
			break;
		case ast_access_member_tree_T: p("access member_tree");
		case ast_access_member_list_T: p("access member_list");
		case ast_access_level_T: p("access");
		case ast_mod_Tifier: p("modifier");
		case ast_constructor_decl_T: p("constructor");
		case ast_constructor_chain_T: p("constructor chain");
		case ast_constructor_chain_this_T: p("this");
		case ast_constructor_chain_super_T: p("super");
		case ast_member_decl_T: p("member_decl");
		case ast_member_decl_list_T: p("member_decl_list");
		case ast_field_decl_T: p("field decl");
		case ast_field_type_name_T:
			printf("type_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_field_access_name_T:
			printf("access_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_prop_decl_T:
			printf("prop %s", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_prop_set_T:
			printf("prop-set");
			break;
		case ast_prop_get_T:
			printf("prop-get");
			break;
		case ast_method_decl_T: p("method decl");
		case ast_method_name_T:
			printf("method_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameter_list_T: p("parameter-list");
		case ast_parameter_T: p("parameter");
		case ast_parameter_type_name_T:
			printf("parameter_type_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameter_access_name_T:
			printf("parameter_access_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_method_return_name_T:
			printf("method_return_name(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_field_access_T: p("field-access");
		case ast_static_field_access_T: p("static-field-access");
		case ast_scope_T: p("scope");
		case ast_stmt_T: p("stmt");
		case ast_stmt_list_T: p("stmt list");
		case ast_if_T: p("if");
		case ast_if_else_T: p("if else");
		case ast_if_elif_list_T: p("if elif_list");
		case ast_if_elif_list_else_T: p("if elif_list else");
		case ast_elif_T: p("elif");
		case ast_else_T: p("else");
		case ast_return_T: p("return");
		case ast_subscript_access: p("[]");
		case ast_blank_T:
			printf("blank");
			break;
		case ast_function_decl_T: p("function decl");
		case ast_function_name_T: p("function name");
		case ast_function_return_name_T: p("function return name");
		case ast_while_T: p("while");
		case ast_true_T: p("true");
		case ast_false_T: p("false");
		case ast_break_T: p("break");
		case ast_continue_T: p("continue");
		case ast_enum_decl_T:
			printf("enum(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_identifier_list_T: p("ident list");
		case ast_inferenced_type_init_T: p("var init");
		case ast_stmt_throw_T: p("throw");
		case ast_stmt_try_T: p("try");
		case ast_stmt_catch_list_T: p("catch list");
		case ast_stmt_catch_T: p("catch");
		case ast_yield_return_T: p("yield return");
		case ast_yield_break_T: p("yield break");
		case ast_null_T: p("null");
		case ast_as_T: p("as");
		case ast_type_parameter_T: 
			printf("type parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_in_parameter_T:
			printf("type in parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_out_parameter_T:
			printf("type out parameter(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_parameterized_typename:
			printf("typename(%s)", string_pool_ref2str(self->u.stringv_value));
			break;
		case ast_type_parameter_list_T: p("type parameter list");
		case ast_type_parameter_rule_list_T: p("type parameter rule list");
		case ast_stmt_assert_T: p("assert");
		case ast_typename_list_T: p("typename list");
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
	return self == NULL || self->tag == ast_blank_T;
}

bool ast_is_access(ast * self) {
	return self->tag == ast_access_level_T;
}

bool ast_is_modifier(ast * self) {
	return self->tag == ast_mod_Tifier;
}

bool ast_is_stmt(ast* self) {
	switch(self->tag) {
		case ast_stmt_T:
		case ast_stmt_list_T:
		case ast_stmt_variable_decl_T:
		case ast_stmt_variable_init_T:
		case ast_inferenced_type_init_T:
		case ast_if_T:
		case ast_if_elif_list_T:
		case ast_if_elif_list_else_T:
		case ast_elif_T:
		case ast_else_T:
		case ast_while_T:
		case ast_continue_T:
		case ast_break_T:
		case ast_proc_T:
		case ast_stmt_assert_T:
		case ast_stmt_try_T:
		case ast_stmt_catch_T:
		case ast_stmt_catch_list_T:
		case ast_stmt_defer_T:
		case ast_inject_jni_value_T:
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
	if(self->tag == ast_mod_Tifier_list) {
		return ast_cast_to_modifierImpl(self, error);
	}
	assert(ast_is_modifier(self));
	return self->u.modifier_value;
}

constructor_chain_type ast_cast_to_chain_type(ast * self) {
	switch (self->tag) {
		case ast_constructor_chain_this_T:
			return chain_type_this_T;
		case ast_constructor_chain_super_T:
			return chain_type_super_T;
		default:
			break;
	}
	return chain_type_super_T;
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