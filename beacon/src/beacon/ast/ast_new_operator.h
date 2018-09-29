#pragma once
#ifndef BEACON_AST_AST_NEW_OPERATOR_H
#define BEACON_AST_AST_NEW_OPERATOR_H
#include "ast.h"
#include "assign_operator_type.h"
//typedef struct ast { } ast;

/**
 * 単項演算子を表す要素を作成します.
 * @param tag
 * @param a
 * @return
 */
ast* NewASTUnary(ast_tag tag, ast* a);

/**
 * 二項演算子を表す要素を作成します.
 * @param tag
 * @param aleft
 * @param aright
 * @return
 */
ast* NewASTBinary(ast_tag tag, ast* aleft, ast* aright);
#endif // !SIGNAL_AST_AST_NEW_OPERATOR_H
