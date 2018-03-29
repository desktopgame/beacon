#pragma once
#ifndef SIGNAL_AST_AST_H
#define SIGNAL_AST_AST_H
#include <stdint.h>
#include <stdbool.h>
#include "access_level.h"
#include "modifier_type.h"
#include "constructor_chain_type.h"
#include "../util/list.h"
/**
 * AST(AbstractSourceTree) の種類を表すタグです.
 */
typedef enum ast_tag {
	ast_root,
	ast_blank,
	//+ - * / %
	ast_add,
	ast_sub,
	ast_mul,
	ast_div,
	ast_mod,
	ast_lshift,
	ast_rshift,
	//| ||
	ast_bit_or,
	ast_logic_or,
	//& &&
	ast_bit_and,
	ast_logic_and,
	ast_exc_or,
	ast_childa,
	//= += -= *= /= %=
	ast_assign,
	ast_add_assign,
	ast_sub_assign,
	ast_mul_assign,
	ast_div_assign,
	ast_mod_assign,
	ast_or_assign,
	ast_and_assign,
	ast_exc_or_assign,
	ast_lshift_assign,
	ast_rshift_assign,
	//== !=
	ast_equal,
	ast_notequal,
	//> >= < <=
	ast_gt,
	ast_ge,
	ast_lt,
	ast_le,
	//! -
	ast_not,
	ast_pos,
	ast_neg,
	//++ --
	ast_pre_inc,
	ast_pre_dec,
	ast_post_inc,
	ast_post_dec,
	//() (...)
	ast_op_call,
	//int double
	ast_int,
	ast_double,
	ast_char,
	ast_string,
	ast_cast,
	ast_variable,
	ast_inferenced_type_init,
	ast_call,
	ast_invoke,
	ast_return,
	ast_this,
	ast_super,
	ast_new_instance,

	ast_field_access,
	ast_static_field_access,

	ast_identifier,
	ast_identifier_list,
	//ast_typename,

	//ast_variable_decl,

	ast_namespace_decl,
	ast_namespace_body,
	ast_namespace_member_decl,
	ast_namespace_member_decl_list,
	ast_namespace_path,
	ast_namespace_path_list,

	ast_import_decl,
	ast_import_path,

	ast_class_decl_unit,
	//ast_class_decl_list,
	ast_class_decl,
	ast_enum_decl,
	ast_interface_decl,
	ast_class_super,

	ast_access_public,
	ast_access_private,
	ast_access_protected,
	ast_access_member_list,
	ast_access_member_tree,

	ast_modifier_none,
	ast_modifier_static,
	ast_modifier_native,
	ast_modifier_static_native,

	ast_member_decl,
	ast_member_decl_list,

	ast_field_decl,
	ast_field_type_name,
	ast_field_access_name,

	ast_function_decl,
	ast_function_name,
	ast_function_return_name,

	ast_method_decl,
	ast_method_name,
	ast_method_return_name,

	ast_constructor_decl,
	ast_constructor_chain,
	ast_constructor_chain_this,
	ast_constructor_chain_super,

	ast_true,
	ast_false,
	ast_null,
	ast_as,

	ast_scope,
	ast_stmt,
	ast_while,
	ast_break,
	ast_continue,
	//
	//call(); 
	//a.invoke();
	//のような、式によってのみ構成される文(ステートメント)
	//を特別にプロセスと呼称します。
	//
	ast_proc,
	ast_stmt_list,
	ast_name_reference,
	ast_typename,
	ast_typename_list,
	ast_stmt_variable_decl,
	ast_stmt_variable_init,

	ast_stmt_try,
	ast_stmt_catch,
	ast_stmt_catch_list,
	ast_stmt_throw,

	ast_parameter,
	ast_parameter_type_name,
	ast_parameter_access_name,
	ast_parameter_list,

	ast_argument,
	ast_argument_list,

	ast_fqcn,
	ast_fqcn_class_name,
	ast_fqcn_part,
	ast_fqcn_part_list,

	ast_parameterized_typename,
	ast_type_parameter,
	ast_type_in_parameter,
	ast_type_out_parameter,
	ast_type_parameter_list,

	ast_type_parameter_rule_list,

	ast_static_invoke,
	//stmt
	ast_if,
	ast_else,
	ast_if_else,
	ast_if_elif_list,
	ast_if_elif_list_else,
	ast_elif_list,
	ast_elif,
} ast_tag;

/**
 * ソースコード中の要素を表します.
 */
typedef struct ast {
	union {
		int int_value;
		double double_value;
		char char_value;
		char* string_value;
	} u;
	ast_tag tag;
	uint32_t child_count;
	uint32_t lineno;
	list* children;
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
 * @param name
 * @return
 */
ast* ast_new_namespace_path(char* name);

/**
 * 二つの名前空間を連結します.
 * @param forward
 * @param name
 * @return
 */
ast* ast_new_namespace_path_list(ast* forward, char* name);

/**
 * インポート先のファイルを表す要素を作成します.
 * @param str
 * @return
 */
ast* ast_new_import_path(ast* str);

/**
 * インポート宣言を表す要素を作成します.
 * @param import_path
 * @return
 */
ast* ast_new_import_decl(ast* import_path);

/**
 * スコープ({ ... }) を表す要素を作成します.
 * @param stmt_list
 * @return
 */
ast* ast_new_scope(ast* stmt_list);

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
 * @param str
 * @return
 */
ast* ast_new_identifier(char* str);

/**
 * 識別子のリストを表す要素を作成します.
 * @param str
 * @param ident_list
 * @return
 */
ast* ast_new_identifier_list(char* str, ast* ident_list);

/**
 * 計算可能な要素だけで構成される文を作成します.
 * @param expr
 * @return
 */
ast* ast_new_proc(ast* expr);

/**
 * self に child を子要素として追加します.
 * @param self
 * @param child
 */
ast* ast_push(ast* self, ast* child);

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
 * 指定の要素がアクセスレベルを表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
access_level ast_cast_to_access(ast* self);

/**
 * 指定の要素が修飾子を表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
modifier_type ast_cast_to_modifier(ast* self);

/**
 * 指定の要素が連鎖を表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
constructor_chain_type ast_cast_to_chain_type(ast* self);
#endif // !SIGNAL_AST_AST_H