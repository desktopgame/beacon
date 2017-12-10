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

/**
 * ifを表す要素を作成します.
 * @param cond
 * @param body
 * @return
 */
ast* ast_new_if(ast* cond, ast* body);

/** 
 * elseを表す要素を作成します.
 * @param body
 * @return
 */
ast* ast_new_else(ast* body);

/**
 * if-elseを表す要素を作成します.
 * @param cond
 * @param trueBody
 * @param falseBody
 * @return
 */
ast* ast_new_if_else(ast* cond, ast* trueBody, ast* falseBody);

/**
 * if-elif... を表す要素を作成します.
 * @param cond
 * @param trueBody
 * @param elifList
 * @return
 */
ast* ast_new_if_elif_list(ast* cond, ast* trueBody, ast* elifList);

/**
 * if-elif...-elseを表す要素を作成します.
 * @param cond
 * @param trueBody
 * @param elifList
 * @param elseBody
 * @param
 */
ast* ast_new_if_elif_list_else(ast* cond, ast* trueBody, ast* elifList, ast* elseBody);

/**
 * elif...を表す要素を作成します.
 * @param forward
 * @param tail
 * @return
 */
ast* ast_new_elif_list(ast* forward, ast* tail);

/**
 * elifを表す要素を作成します.
 * @param cond
 * @param body
 * @return
 */
ast* ast_new_elif(ast* cond, ast* body);

/**
* 実引数を表す要素を作成します.
* @param factor
* @return
*/
ast* ast_new_argument(ast* factor);

/**
* 実引数を表す要素を作成します.
* @param factor
* @param argument_list
* @return
*/
ast* ast_new_argument_list(ast* factor, ast* argument_list);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
