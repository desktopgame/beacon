#pragma once
#ifndef BEACON_AST_AST_NEW_LITERAL_H
#define BEACON_AST_AST_NEW_LITERAL_H
#include "ast.h"

/**
 * 整数型の値を保存する要素を作成します.
 * @param i
 */
AST* NewASTInt(int i);

/**
 * 実数型の値を保存する要素を作成します.
 * @param d
 */
AST* NewASTDouble(double d);

/**
 * 文字を保存する要素を作成します.
 * @param ch
 * @return
 */
AST* NewASTChar(char ch);

/**
 * 文字を保存する要素を作成します.
 * @param sv
 * @return
 */
AST* NewASTString(StringView sv);
#endif // !SIGNAL_AST_AST_NEW_LITERAL_H
