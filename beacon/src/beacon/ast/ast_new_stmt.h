#pragma once
#ifndef BEACON_AST_AST_NEW_STMT_H
#define BEACON_AST_AST_NEW_STMT_H
#include "ast.h"

/**
 * 実行可能な文を表す要素を作成します.
 */
#define ast_new_stmt(stmt) (MallocASTStmt(stmt, __FILE__, __LINE__))

/**
 * 実行可能な文を表す要素を作成します.
 * @param astmt
 * @param filename
 * @param lineno
 * @return
 */
ast* MallocASTStmt(ast* astmt, const char* filename, int lineno);

/**
 * 実行可能な文を表す要素を作成します. 
 * @param astmt
 * @param astmt_list
 * @return
 */
ast* NewASTStmtList(ast* astmt, ast* astmt_list);

/**
 * ifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* NewASTIf(ast* acond, ast* abody);

/** 
 * elseを表す要素を作成します.
 * @param abody
 * @return
 */
ast* NewASTElse(ast* abody);

/**
 * if-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param afalseBody
 * @return
 */
ast* NewASTIfElse(ast* acond, ast* atrueBody, ast* afalseBody);

/**
 * if-elif... を表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @return
 */
ast* NewASTIfElifList(ast* acond, ast* atrueBody, ast* aelifList);

/**
 * if-elif...-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @param aelseBody
 * @param
 */
ast* NewASTIfElifListElse(ast* acond, ast* atrueBody, ast* aelifList, ast* aelseBody);

/**
 * elif...を表す要素を作成します.
 * @param aforward
 * @param atail
 * @return
 */
ast* NewASTElifList(ast* aforward, ast* atail);

/**
 * elifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* NewASTElif(ast* acond, ast* abody);

/**
 * whileを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
ast* NewASTWhile(ast* acond, ast* abody);

/** 
 * ループから抜けるステートメントを作成します.
 * @return
 */
ast* NewASTBreak();

/**
 * 次のループまでスキップするステートメントを作成します.
 * @return
 */
ast* NewASTContinue();

/**
 * 値を返却するステートメントを作成します.
 * @param afact
 * @return
 */
ast* NewASTReturn(ast* afact);

/**
 * @return
 */
ast* NewASTReturnEmpty();

/**
 * 例外をスローするステートメントを作成します.
 * @param afact
 * @return
 */
ast* NewASTThrow(ast* afact);

/**
 * 例外が発生するかもしれない処理を囲うステートメント.
 * @param abody
 * @param acatch_list
 */
ast* NewASTTry(ast* abody, ast* acatch_list);

/**
 * 例外を捕捉するステートメントを作成します.
 * @param typename
 * @param snamev
 * @param abody
 * @return
 */
ast* NewASTCatch(ast* stypename, StringView snamev, ast* abody);

/**
 * キャッチ節の一覧を作成します.
 * @param acatch
 * @param acatch_list
 * @return
 */
ast* NewASTCatchList(ast* acatch, ast* acatch_list);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @return
*/
ast* NewASTArgument(ast* afactor);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @param aargument_list
* @return
*/
ast* NewASTArgumentList(ast* factor, ast* argument_list);

/**
 * 完全クラス名(XX::YY::Foo)を表す要素を作成します.
 * @param apart_list
 * @param class_name
 * @return
 */
ast* NewASTFQCN(ast* part_list, StringView class_namev);

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 */
#define NewASTFQCN_part(name) (MallocASTFQCNPart(name, __FILE__, __LINE__))

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 * @param name
 * @param filename
 * @param lineno
 * @return
 */
ast* MallocASTFQCNPart(StringView namev, const char* filename, int lineno);

/**
 * 完全修飾クラス名の名前空間部分(XX::YY::)の一覧を表す要素を作成します.
 * @param apart
 * @param apart_list
 * @return
 */
ast* NewASTFQCNPartList(ast* part, ast* part_list);

/**
 * X::Y y; を表す要素を作成します.
 * @param atype
 * @param namev
 * @return
 */
ast* NewASTVariableDecl(ast* type, StringView namev);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param atype
 * @param namev
 * @param afact
 * @return
 */
ast* NewASTVariableInit(ast* type, StringView namev, ast* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param afact
 * @return
 */
ast* NewASTInferencedTypeInit(StringView namev, ast* fact);

/**
 * assert 条件 を表す要素を作成します.
 * @param afact
 * @param amsg
 * @return
 */
ast* NewASTAssert(ast* afact, ast* amsg);

/**
 * 強制実行を表す要素を作成します.
 * @param astmt
 * @return
 */
ast* NewASTDefer(ast* astmt);

/**
 * コルーチンの区切りを表す要素を作成します.
 * @param afact
 * @return
 */
ast* NewASTYieldReturn(ast* afact);

/**
 * コルーチンの終了を表す要素を作成します.
 * @return
 */
ast* NewASTYieldBreak();

/**
 * Javaから beacon が実行される時、事前に定義されたテーブルを注入するためのノード.
 * @param namev 変数名
 * @param avalue 値
 * @return
 */
ast* NewASTInject(StringView namev, ast* avalue);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
