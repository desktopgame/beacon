#pragma once
#ifndef SIGNAL_AST_AST_NEW_OPERATOR_H
#define SIGNAL_AST_AST_NEW_OPERATOR_H
#include "ast.h"
#include "assign_operator_type.h"
//typedef struct ast { } ast;

/**
 * 単項演算子を表す要素を作成します.
 * @param tag
 * @param a
 * @return
 */
ast* ast_new_unary(ast_tag tag, ast* a);

/**
 * 二項演算子を表す要素を作成します.
 * @param tag
 * @param left
 * @param right
 * @return
 */
ast* ast_new_binary(ast_tag tag, ast* left, ast* right);
#endif // !SIGNAL_AST_AST_NEW_OPERATOR_H
