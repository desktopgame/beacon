#pragma once
#ifndef SIGNAL_AST_AST_NEW_STMT_H
#define SIGNAL_AST_AST_NEW_STMT_H
#include "ast.h"

/**
 * 変数宣言を表す要素を作成します.
 * @param typename
 * @param identifier,
 * @param expr
 * @return
 */
ast* ast_new_variable_decl(ast* type_name, ast* identifier, ast* expr);

/**
 * 実行可能な文を表す要素を作成します.
 * @param stmt
 * @return
 */
ast* ast_new_stmt(ast* stmt);

/**
 * 実行可能な文を表す要素を作成します. 
 * @param stmt
 * @param stmt_list
 * @return
 */
ast* ast_new_stmt_list(ast* stmt, ast* stmt_list);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
