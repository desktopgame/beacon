#pragma once
#ifndef BEACON_AST_AST_H
#define BEACON_AST_AST_H
#include <stdint.h>
#include <stdbool.h>
#include "access_level.h"
#include "modifier_type.h"
#include "constructor_chain_type.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "operator_type.h"
/**
 * AST(AbstractSourceTree) の種類を表すタグです.
 */
typedef enum ast_tag {
	ast_root_T,
	ast_blank_T,
	//+ - * / %
	ast_add_T,
	ast_sub_T,
	ast_mul_T,
	ast_div_T,
	ast_mod_T,
	ast_lshift_T,
	ast_rshift_T,
	//| ||
	ast_bit_or_T,
	ast_logic_or_T,
	//& &&
	ast_bit_and_T,
	ast_logic_and_T,
	ast_exc_or_T,
	ast_childa_T,
	//= += -= *= /= %=
	ast_as_Tsign_T,
	ast_add_T_assign,
	ast_sub_T_assign,
	ast_mul_T_assign,
	ast_div_T_assign,
	ast_mod_T_assign,
	ast_or_assign_T,
	ast_and_assign_T,
	ast_exc_or_T_assign,
	ast_lshift_T_assign,
	ast_rshift_T_assign,
	//== !=
	ast_equal_T,
	ast_not_Tequal_T,
	//> >= < <=
	ast_gt_T,
	ast_ge_T,
	ast_lt_T,
	ast_le_T,
	//a is b
	ast_instanceof_T,
	//! -
	ast_not_T,
	ast_pos_T,
	ast_neg_T,
	//() (...)
	ast_op_call_T,
	//int double
	ast_int_T,
	ast_double_T,
	ast_char_T,
	ast_string_T,
	ast_cast_T,
	ast_variable_T,
	ast_inferenced_type_init_T,
	ast_call_T,
	ast_invoke_T,
	ast_sub_Tscript_access,
	ast_return_T,
	ast_return_T_empty,
	ast_this_T,
	ast_super_T,
	ast_new_instance_T,
	ast_lambda_T,

	ast_field_access_T,
	ast_static_field_access_T,

	ast_identifier_T,
	ast_identifier_T_list,
	//ast_typename_T,

	//ast_variable_T_decl,

	ast_namespace_decl_T,
	ast_namespace_body_T,
	ast_namespace_member_decl_T,
	ast_namespace_member_decl_T_list,
	ast_namespace_path_T,
	ast_namespace_path_T_list,

	ast_import_decl_T,
	ast_import_decl_T_list,
	ast_import_path_T,

	ast_class_decl_T_unit_T,
	//ast_class_decl_T_list,
	ast_abstract_class_decl_T,
	ast_class_decl_T,
	ast_enum_decl_T,
	ast_int_Terface_decl,
	ast_class_super_T,

	ast_access_level_T,
	ast_access_member_list_T,
	ast_access_member_tree_T,

	ast_member_decl_T,
	ast_member_decl_T_list,

	ast_operator_overload_T,

	ast_field_decl_T,
	ast_field_type_name_T,
	ast_field_access_T_name,

	ast_prop_set_T,
	ast_prop_get_T,
	ast_prop_decl_T,

	ast_mod_Tifier_list,
	ast_mod_Tifier,

	ast_function_decl_T,
	ast_function_name_T,
	ast_function_return_name_T,

	ast_method_decl_T,
	ast_method_name_T,
	ast_method_return_name_T,

	ast_constructor_decl_T,
	ast_constructor_chain_T,
	ast_constructor_chain_T_this,
	ast_constructor_chain_T_super,
	ast_explicit_bioperator_T,
	ast_explicit_uoperator_T,

	ast_true_T,
	ast_false_T,
	ast_null_T,
	ast_as_T,

	ast_scope_T,
	ast_stmt_T,
	ast_while_T,
	ast_break_T,
	ast_continue_T,
	ast_yield_return_T,
	ast_yield_break_T,
	//
	//call(); 
	//a.invoke();
	//のような、式によってのみ構成される文(ステートメント)
	//を特別にプロセスと呼称します。
	//
	ast_proc_T,
	ast_stmt_T_list,
	ast_name_reference_T,
	ast_typename_T,
	ast_typename_T_list,
	ast_stmt_T_variable_decl,
	ast_stmt_T_variable_init,
	ast_stmt_T_defer,

	ast_stmt_T_try,
	ast_stmt_T_catch,
	ast_stmt_T_catch_list,
	ast_stmt_T_throw,

	ast_stmt_T_assert,

	ast_parameter_T,
	ast_parameter_T_type_name,
	ast_parameter_T_access_name,
	ast_parameter_T_list,

	ast_argument_T,
	ast_argument_T_list,

	ast_fqcn_T,
	ast_fqcn_T_class_name,
	ast_fqcn_T_part,
	ast_fqcn_T_part_list,

	ast_parameter_Tized_typename,
	ast_type_parameter_T,
	ast_type_in_parameter_T,
	ast_type_out_parameter_T,
	ast_type_parameter_T_list,

	ast_type_parameter_T_rule_list,

	ast_static_invoke_T,
	//stmt
	ast_if_T,
	ast_else_T,
	ast_if_T_else,
	ast_if_T_elif_list,
	ast_if_T_elif_list_else,
	ast_elif_T_list_T,
	ast_elif_T,
} ast_tag;

/**
 * ソースコード中の要素を表します.
 */
typedef struct ast {
	union {
		int int_value;
		double double_value;
		char char_value;
		string_view stringv_value;
		access_level access_value;
		modifier_type modifier_value;
		operator_type operator_value;
	} u;
	ast_tag tag;
	//uint32_t child_count;
	uint32_t lineno;
	vector* vchildren;
	//list* children;
} ast;

/**
 * 現在のコンパイラに AST を追加します.
 * @param self
 */
void ast_compile_entry(ast* self);

/**
 * 指定のタグで子要素を持たない AST を作成します.
 */
#define ast_new(tag) (ast_malloc(tag, __FILE__, __LINE__))

/**
 * 指定のタグで子要素を持たない AST を作成します.
 * @param tag
 * @param filename
 * @param lineno
 */
ast* ast_malloc(ast_tag tag, const char* filename, int lineno);

/**
 * 名前空間の一節(. ~~~ .)を表す要素を作成します.
 * @param namev
 * @return
 */
ast* ast_new_namespace_path(string_view namev);

/**
 * 二つの名前空間を連結します.
 * @param aforward
 * @param namev
 * @return
 */
ast* ast_new_namespace_path_list(ast* aforward, string_view namev);

/**
 * インポート先のファイルを表す要素を作成します.
 * @param astr
 * @return
 */
ast* ast_new_import_path(ast* astr);

/**
 * インポート宣言を表す要素を作成します.
 * @param aimport_path
 * @return
 */
ast* ast_new_import_decl(ast* aimport_path);

/**
 * インポートの一覧を表す要素を作成します.
 * @param aimport
 * @param aimport_list
 * @return
 */
ast* ast_new_import_decl_list(ast* aimport, ast* aimport_list);

/**
 * スコープ({ ... }) を表す要素を作成します.
 * @param astmt_list
 * @return
 */
ast* ast_new_scope(ast* astmt_list);

/**
 * 空のスコープを表す要素を作成します.
 * @return
 */
ast* ast_new_scope_empty();

/**
 * 空の要素を作成します.
 */
ast* ast_new_blank();

/**
 * 識別子を表す要素を作成します.
 * @param strv
 * @return
 */
ast* ast_new_identifier(string_view strv);

/**
 * 識別子のリストを表す要素を作成します.
 * @param strv
 * @param aident_list
 * @return
 */
ast* ast_new_identifier_list(string_view strv, ast* aident_list);

/**
 * 計算可能な要素だけで構成される文を作成します.
 * @param aexpr
 * @return
 */
ast* ast_new_proc(ast* aexpr);

/**
 * self に child を子要素として追加します.
 * @param self
 * @param achild
 */
ast* ast_push(ast* self, ast* achild);

/** 
 * 指定位置の子要素を返します.
 * @param self
 * @param index
 */
ast* ast_at(ast* self, int index);

/**
 * 最初の子要素を返します.
 * @param self
 * @return
 */
ast* ast_first(ast* self);

/**
 * 二番目の子要素を返します.
 * @param self
 * @return
 */
ast* ast_second(ast* self);

/**
 * ツリー形式で全てのタグを出力します.
 * @param self
 */
void ast_print_tree(ast* self);

/**
 * 指定のタグを出力します.
 * @param self
 */
void ast_print(ast* self);

/**
 * 指定の AST とその子要素を全て開放します.
 * @param self
 */
void ast_delete(ast* self);

/**
 * 指定の要素が空なら true.
 * @param self
 * @return
 */
bool ast_is_blank(ast* self);

/**
 * 指定の要素がアクセスレベルなら true.
 * @param self
 * @return
 */
bool ast_is_access(ast* self);

/**
 * 指定の要素が修飾子なら true.
 * @param self
 * @return
 */
bool ast_is_modifier(ast* self);

/**
 * 指定の要素がステートメントなら true.
 * @param self
 * @return
 */
bool ast_is_stmt(ast* self);

/**
 * 指定の要素がアクセスレベルを表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
access_level ast_cast_T_to_access(ast* self);

/**
 * 指定の要素が修飾子を表す要素なら列挙型に変換します.
 * @param self
 * @param error
 * @return
 */
modifier_type ast_cast_T_to_modifier(ast* self, bool* error);

/**
 * 指定の要素が連鎖を表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
constructor_chain_type ast_cast_T_to_chain_type(ast* self);
#endif // !SIGNAL_AST_AST_H
