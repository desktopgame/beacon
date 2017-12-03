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
#endif // !SIGNAL_AST_AST_NEW_STMT_H
