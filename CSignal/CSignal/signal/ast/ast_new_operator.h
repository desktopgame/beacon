#pragma once
#ifndef SIGNAL_AST_AST_NEW_OPERATOR_H
#define SIGNAL_AST_AST_NEW_OPERATOR_H
#include "ast.h"
//typedef struct ast { } ast;
/**
* 加算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_add(ast* l, ast* r);

/**
* 減算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_sub(ast* l, ast* r);

/**
* 乗算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_mul(ast* l, ast* r);

/**
* 除算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_div(ast* l, ast* r);

/**
* 剰余を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_mod(ast* l, ast* r);
#endif // !SIGNAL_AST_AST_NEW_OPERATOR_H
