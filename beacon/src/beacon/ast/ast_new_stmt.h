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
 * @param astmt
 * @param filename
 * @param lineno
 * @return
 */
ast* ast_malloc_stmt(ast* astmt, const char* filename, int lineno);

/**
 * 実行可能な文を表す要素を作成します. 
 * @param astmt
 * @param astmt_list
 * @return
 */
ast* ast_new_stmt_list(ast* astmt, ast* astmt_list);

/**
 * ifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* ast_new_if(ast* acond, ast* abody);

/** 
 * elseを表す要素を作成します.
 * @param abody
 * @return
 */
ast* ast_new_else(ast* abody);

/**
 * if-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param afalseBody
 * @return
 */
ast* ast_new_if_else(ast* acond, ast* atrueBody, ast* afalseBody);

/**
 * if-elif... を表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @return
 */
ast* ast_new_if_elif_list(ast* acond, ast* atrueBody, ast* aelifList);

/**
 * if-elif...-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @param aelseBody
 * @param
 */
ast* ast_new_if_elif_list_else(ast* acond, ast* atrueBody, ast* aelifList, ast* aelseBody);

/**
 * elif...を表す要素を作成します.
 * @param aforward
 * @param atail
 * @return
 */
ast* ast_new_elif_list(ast* aforward, ast* atail);

/**
 * elifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* ast_new_elif(ast* acond, ast* abody);

/**
 * whileを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* ast_new_while(ast* acond, ast* abody);

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
 * @param afact
 * @return
 */
ast* ast_new_return(ast* afact);

/**
 * @return
 */
ast* ast_new_return_empty();

/**
 * 例外をスローするステートメントを作成します.
 * @param afact
 * @return
 */
ast* ast_new_throw(ast* afact);

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
* @param afactor
* @return
*/
ast* ast_new_argument(ast* afactor);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @param aargument_list
* @return
*/
ast* ast_new_argument_list(ast* factor, ast* argument_list);

/**
 * 完全クラス名(XX::YY::Foo)を表す要素を作成します.
 * @param apart_list
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
 * @param apart
 * @param apart_list
 * @return
 */
ast* ast_new_fqcn_part_list(ast* part, ast* part_list);

/**
 * X::Y y; を表す要素を作成します.
 * @param atype
 * @param namev
 * @return
 */
ast* ast_new_variable_decl(ast* type, string_view namev);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param atype
 * @param namev
 * @param afact
 * @return
 */
ast* ast_new_variable_init(ast* type, string_view namev, ast* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param afact
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

/**
 * Javaから beacon が実行される時、事前に定義されたテーブルを注入するためのノード.
 * @param namev 変数名
 * @param avalue 値
 * @return
 */
ast* ast_new_inject(string_view namev, ast* avalue);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
