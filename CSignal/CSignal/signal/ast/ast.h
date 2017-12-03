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
 * 空の要素を作成します.
 */
ast* ast_new_blank();

/**
 * 整数型の値を保存する要素を作成します.
 * @param i
 */
ast* ast_new_int(int i);

/**
 * 実数型の値を保存する要素を作成します.
 * @param d
 */
ast* ast_new_double(double d);

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
