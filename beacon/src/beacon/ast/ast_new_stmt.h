//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file ast_new_stmt.h
 * @brief ステートメントを表すAST要素の生成関数を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_AST_AST_NEW_STMT_H
#define BEACON_AST_AST_NEW_STMT_H
#include "ast.h"

/**
 * 実行可能な文を表す要素を作成します.
 */
#define bc_NewASTStmt(stmt) (bc_MallocASTStmt(stmt, __FILE__, __LINE__))

/**
 * 実行可能な文を表す要素を作成します.
 * @param astmt
 * @param filename
 * @param lineno
 * @return
 */
bc_AST* bc_MallocASTStmt(bc_AST* astmt, const char* filename, int lineno);

/**
 * 実行可能な文を表す要素を作成します. 
 * @param astmt
 * @param astmt_list
 * @return
 */
bc_AST* bc_NewASTStmtList(bc_AST* astmt, bc_AST* astmt_list);

/**
 * ifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
bc_AST* bc_NewASTIf(bc_AST* acond, bc_AST* abody);

/** 
 * elseを表す要素を作成します.
 * @param abody
 * @return
 */
bc_AST* bc_NewASTElse(bc_AST* abody);

/**
 * if-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param afalseBody
 * @return
 */
bc_AST* bc_NewASTIfElse(bc_AST* acond, bc_AST* atrueBody, bc_AST* afalseBody);

/**
 * if-elif... を表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @return
 */
bc_AST* bc_NewASTIfElifList(bc_AST* acond, bc_AST* atrueBody, bc_AST* aelifList);

/**
 * if-elif...-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @param aelseBody
 * @param
 */
bc_AST* bc_NewASTIfElifListElse(bc_AST* acond, bc_AST* atrueBody, bc_AST* aelifList, bc_AST* aelseBody);

/**
 * elif...を表す要素を作成します.
 * @param aforward
 * @param atail
 * @return
 */
bc_AST* bc_NewASTElifList(bc_AST* aforward, bc_AST* atail);

/**
 * elifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
bc_AST* bc_NewASTElif(bc_AST* acond, bc_AST* abody);

/**
 * whileを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
bc_AST* bc_NewASTWhile(bc_AST* acond, bc_AST* abody);

/** 
 * ループから抜けるステートメントを作成します.
 * @return
 */
bc_AST* bc_NewASTBreak();

/**
 * 次のループまでスキップするステートメントを作成します.
 * @return
 */
bc_AST* bc_NewASTContinue();

/**
 * 値を返却するステートメントを作成します.
 * @param afact
 * @return
 */
bc_AST* bc_NewASTReturn(bc_AST* afact);

/**
 * @return
 */
bc_AST* bc_NewASTReturnEmpty();

/**
 * 例外をスローするステートメントを作成します.
 * @param afact
 * @return
 */
bc_AST* bc_NewASTThrow(bc_AST* afact);

/**
 * 例外が発生するかもしれない処理を囲うステートメント.
 * @param abody
 * @param acatch_list
 */
bc_AST* bc_NewASTTry(bc_AST* abody, bc_AST* acatch_list);

/**
 * 例外を捕捉するステートメントを作成します.
 * @param typename
 * @param name
 * @param abody
 * @return
 */
bc_AST* bc_NewASTCatch(bc_AST* stypename, StringView name, bc_AST* abody);

/**
 * キャッチ節の一覧を作成します.
 * @param acatch
 * @param acatch_list
 * @return
 */
bc_AST* bc_NewASTCatchList(bc_AST* acatch, bc_AST* acatch_list);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @return
*/
bc_AST* bc_NewASTArgument(bc_AST* afactor);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @param aargument_list
* @return
*/
bc_AST* bc_NewASTArgumentList(bc_AST* factor, bc_AST* argument_list);

/**
 * 完全クラス名(XX::YY::Foo)を表す要素を作成します.
 * @param apart_list
 * @param class_name
 * @return
 */
bc_AST* bc_NewASTFQCN(bc_AST* part_list, StringView class_name);

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 */
#define bc_NewASTFQCNPart(name) (bc_MallocASTFQCNPart(name, __FILE__, __LINE__))

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 * @param name
 * @param filename
 * @param lineno
 * @return
 */
bc_AST* bc_MallocASTFQCNPart(StringView namev, const char* filename, int lineno);

/**
 * 完全修飾クラス名の名前空間部分(XX::YY::)の一覧を表す要素を作成します.
 * @param apart
 * @param apart_list
 * @return
 */
bc_AST* bc_NewASTFQCNPartList(bc_AST* part, bc_AST* part_list);

/**
 * X::Y y; を表す要素を作成します.
 * @param atype
 * @param name
 * @return
 */
bc_AST* bc_NewASTVariableDecl(bc_AST* type, StringView name);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param atype
 * @param name
 * @param afact
 * @return
 */
bc_AST* bc_NewASTVariableInit(bc_AST* type, StringView name, bc_AST* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param afact
 * @return
 */
bc_AST* bc_NewASTInferencedTypeInit(StringView name, bc_AST* fact);

/**
 * assert 条件 を表す要素を作成します.
 * @param afact
 * @param amsg
 * @return
 */
bc_AST* bc_NewASTAssert(bc_AST* afact, bc_AST* amsg);

/**
 * 強制実行を表す要素を作成します.
 * @param astmt
 * @return
 */
bc_AST* bc_NewASTDefer(bc_AST* astmt);

/**
 * コルーチンの区切りを表す要素を作成します.
 * @param afact
 * @return
 */
bc_AST* bc_NewASTYieldReturn(bc_AST* afact);

/**
 * コルーチンの終了を表す要素を作成します.
 * @return
 */
bc_AST* bc_NewASTYieldBreak();

/**
 * Javaから beacon が実行される時、事前に定義されたテーブルを注入するためのノード.
 * @param name 変数名
 * @param avalue 値
 * @return
 */
bc_AST* bc_NewASTInject(StringView name, bc_AST* avalue);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
