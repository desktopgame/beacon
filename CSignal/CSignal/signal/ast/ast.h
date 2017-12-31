#pragma once
#ifndef SIGNAL_AST_AST_H
#define SIGNAL_AST_AST_H
#include <stdint.h>
#include <stdbool.h>
#include "access_level.h"
#include "modifier_type.h"
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
	//| ||
	ast_bit_or,
	ast_logic_or,
	//& &&
	ast_bit_and,
	ast_logic_and,
	//= += -= *= /= %=
	ast_assign,
	ast_add_assign,
	ast_sub_assign,
	ast_mul_assign,
	ast_div_assign,
	ast_mod_assign,
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
	ast_neg,
	//++ --
	ast_pre_inc,
	ast_pre_dec,
	ast_post_inc,
	ast_post_dec,
	//int double
	ast_int,
	ast_double,
	ast_char,
	ast_string,

	ast_variable,
	ast_call,
	ast_invoke,

	ast_identifier,
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

	ast_func_decl,
	ast_func_name,
	ast_func_return_name,

	ast_constructor_decl,
	ast_constructor_chain,

	ast_scope,
	ast_stmt,
	//
	//call(); 
	//a.invoke();
	//のような、式によってのみ構成される文(ステートメント)
	//を特別にプロセスと呼称します。
	//
	ast_proc,
	ast_stmt_list,
	
	ast_typename,
	ast_stmt_variable_decl,

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
	uint32_t childCount;
	list* children;
} ast;

/**
 * 現在のコンパイラに AST を追加します.
 * @param self
 */
void ast_compile_entry(ast* self);

/**
 * 指定のタグで子要素を持たない AST を作成します.
 * @param tag
 */
ast* ast_new(ast_tag tag);

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
 * 前置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_inc(ast* a);

/**
 * 前置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_dec(ast* a);

/**
 * 後置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_inc(ast* a);

/**
 * 後置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_dec(ast* a);

/**
 * 識別子を表す要素を作成します.
 * @param str
 * @return
 */
ast* ast_new_identifier(char* str);

/**
 * 変数を表す要素を作成します.
 * @param name
 * @return
 */
ast* ast_new_variable(const char* name);

/**
 * 関数呼び出しを表す要素を作成します.
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_call(const char* name, ast* argument_list);

/**
 * メソッド呼び出しを表す要素を作成します.
 * @param receiver
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_invoke(ast* receiver, const char* name, ast* argument_list);

/**
 * 完全修飾名に対するメソッド呼び出しを表す要素を作成します.
 * @param fqcn
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_static_invoke(ast* fqcn, const char* name, ast* argument_list);

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
#endif // !SIGNAL_AST_AST_H
