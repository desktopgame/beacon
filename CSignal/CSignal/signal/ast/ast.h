#pragma once
#ifndef SIGNAL_AST_AST_H
#define SIGNAL_AST_AST_H
#include <stdint.h>
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

	ast_identifier,
	ast_typename,

	ast_variable_decl,

	ast_import_decl,
	ast_import_path,

	ast_class_decl,
	ast_class_super,

	ast_modifier_public,
	ast_modifier_private,
	ast_modifier_protected,
	ast_modifier_static,
	ast_modifier_native,
	ast_modifier_list,

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
	ast_stmt_list,


	ast_parameter,
	ast_parameter_type_name,
	ast_parameter_access_name,
	ast_parameter_list,

	ast_argument,
	ast_argument_list,
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
 * 型名を表す要素を作成します.
 * @param str
 * @return
 */
ast* ast_new_typename(char* str);

/**
 * 識別子を表す要素を作成します.
 * @param str
 * @return
 */
ast* ast_new_identifier(char* str);

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
#endif // !SIGNAL_AST_AST_H
