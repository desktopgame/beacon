#pragma once
#ifndef SIGNAL_AST_AST_NEW_STMT_H
#define SIGNAL_AST_AST_NEW_STMT_H
#include "ast.h"

/**
 * 実行可能な文を表す要素を作成します.
 */
#define ast_new_stmt(stmt) (ast_malloc_stmt(stmt, __FILE__, __LINE__))

/**
 * 実行可能な文を表す要素を作成します.
 * @param stmt
 * @param filename
 * @param lineno
 * @return
 */
ast* ast_malloc_stmt(ast* stmt, const char* filename, int lineno);

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
 * whileを表す要素を作成します.
 * @param cond
 * @param body
 * @return
 */
ast* ast_new_while(ast* cond, ast* body);

/** 
 * ループから抜けるステートメントを作成します.
 * @return
 */
ast* ast_new_break();

/**
 * 次のループまでスキップするステートメントを作成します.
 * @return
 */
ast* ast_new_continue();

/**
 * 値を返却するステートメントを作成します.
 * @param fact
 * @return
 */
ast* ast_new_return(ast* fact);

/**
 * 例外をスローするステートメントを作成します.
 * @param fact
 * @return
 */
ast* ast_new_throw(ast* fact);

/**
 * 例外が発生するかもしれない処理を囲うステートメント.
 * @param abody
 * @param acatch_list
 */
ast* ast_new_try(ast* abody, ast* acatch_list);

/**
 * 例外を捕捉するステートメントを作成します.
 * @param typename
 * @param name
 * @param abody
 * @return
 */
ast* ast_new_catch(ast* stypename, char* sname, ast* abody);

/**
 * キャッチ節の一覧を作成します.
 * @param acatch
 * @param acatch_list
 * @return
 */
ast* ast_new_catch_list(ast* acatch, ast* acatch_list);

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

/**
 * 完全クラス名(XX::YY::Foo)を表す要素を作成します.
 * @param part_list
 * @param class_name
 * @return
 */
ast* ast_new_fqcn(ast* part_list, char* class_name);

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 */
#define ast_new_fqcn_part(name) (ast_malloc_fqcn_part(name, __FILE__, __LINE__))

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 * @param name
 * @param filename
 * @param lineno
 * @return
 */
ast* ast_malloc_fqcn_part(char* name, const char* filename, int lineno);

/**
 * 完全修飾クラス名の名前空間部分(XX::YY::)の一覧を表す要素を作成します.
 * @param part
 * @param part_list
 * @return
 */
ast* ast_new_fqcn_part_list(ast* part, ast* part_list);

/**
 * X::Y y; を表す要素を作成します.
 * @param type
 * @param name
 * @return
 */
ast* ast_new_variable_decl(ast* type, char* name);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param type
 * @param name
 * @param fact
 * @return
 */
ast* ast_new_variable_init(ast* type, char* name, ast* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param fact
 * @return
 */
ast* ast_new_inferenced_type_init(const char* name, ast* fact);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
