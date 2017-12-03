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
 * 指定のタグで子要素を持たない AST を作成します.
 * @param tag
 */
ast* ast_new(ast_tag tag);

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
