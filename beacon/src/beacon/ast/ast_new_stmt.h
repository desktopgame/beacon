#pragma once
#ifndef BEACON_AST_AST_NEW_STMT_H
#define BEACON_AST_AST_NEW_STMT_H
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
 * @param snamev
 * @param abody
 * @return
 */
ast* ast_new_catch(ast* stypename, string_view snamev, ast* abody);

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
ast* ast_new_fqcn(ast* part_list, string_view class_namev);

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
ast* ast_malloc_fqcn_part(string_view namev, const char* filename, int lineno);

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
 * @param namev
 * @return
 */
ast* ast_new_variable_decl(ast* type, string_view namev);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param type
 * @param namev
 * @param fact
 * @return
 */
ast* ast_new_variable_init(ast* type, string_view namev, ast* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param fact
 * @return
 */
ast* ast_new_inferenced_type_init(string_view namev, ast* fact);

/**
 * assert 条件 を表す要素を作成します.
 * @param afact
 * @param amsg
 * @return
 */
ast* ast_new_assert(ast* afact, ast* amsg);

/**
 * 強制実行を表す要素を作成します.
 * @param astmt
 * @return
 */
ast* ast_new_defer(ast* astmt);

/**
 * コルーチンの区切りを表す要素を作成します.
 * @param afact
 * @return
 */
ast* ast_new_yield_return(ast* afact);

/**
 * コルーチンの終了を表す要素を作成します.
 * @return
 */
ast* ast_new_yield_break();
#endif // !SIGNAL_AST_AST_NEW_STMT_H
