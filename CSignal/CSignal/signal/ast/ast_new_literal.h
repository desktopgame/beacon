#pragma once
#ifndef SIGNAL_AST_AST_NEW_LITERAL_H
#define SIGNAL_AST_AST_NEW_LITERAL_H
#include "ast.h"

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
 * 文字を保存する要素を作成します.
 * @param ch
 * @return
 */
ast* ast_new_char(char ch);

/**
 * 文字を保存する要素を作成します.
 * @param ch
 * @return
 */
ast* ast_new_string(char* str);
#endif // !SIGNAL_AST_AST_NEW_LITERAL_H
