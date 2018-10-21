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
AST* NewASTUnary(ASTTag tag, AST* a);

/**
 * 二項演算子を表す要素を作成します.
 * @param tag
 * @param aleft
 * @param aright
 * @return
 */
AST* NewASTBinary(ASTTag tag, AST* aleft, AST* aright);
#endif // !SIGNAL_AST_AST_NEW_OPERATOR_H
