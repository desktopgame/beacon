#pragma once
#ifndef SIGNAL_AST_AST_NEW_FACTOR_H
#define SIGNAL_AST_AST_NEW_FACTOR_H
#include "ast.h"

/**
 * trueを表す要素を作成します.
 * @return
 */
ast* ast_new_true();

/**
 * falseを表す要素を作成します.
 * @return
 */
ast* ast_new_false();

/**
 * キャストを表す要素を作成します.
 * @param atypename
 * @param afact
 * @return
 */
ast* ast_new_cast(ast* atypename, ast* afact);

/**
 * 前置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_inc(ast* a);

/**
 * 前置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_dec(ast* a);

/**
 * 後置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_inc(ast* a);

/**
 * 後置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_dec(ast* a);

/**
 * 変数を表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_variable(ast* a);

/**
 * 関数呼び出しを表す要素を作成します.
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_call(const char* name, ast* argument_list);

/**
 * メソッド呼び出しを表す要素を作成します.
 * @param receiver
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_invoke(ast* receiver, const char* name, ast* argument_list);

/**
 * 完全修飾名に対するメソッド呼び出しを表す要素を作成します.
 * @param fqcn
 * @param name
 * @param argument_list
 * @return
 */
ast* ast_new_static_invoke(ast* fqcn, const char* name, ast* argument_list);

/**
 * thisを表す因子を作成します.
 * @return
 */
ast* ast_new_this();

/**
 * superを表す因子を作成します.
 * @return
 */
ast* ast_new_super();

/**
 * hoge.foo を表す因子を作成します.
 * @param afact
 * @param name
 * @return
 */
ast* ast_new_field_access(ast* afact, char* name);

/**
 * hoge.foo を表す因子を作成します.
 * @param fqcn
 * @param name
 * @return
 */
ast* ast_new_field_access_fqcn(ast* fqcn, char* name);

/**
 * new X::Y(...) を表す因子を作成します.
 * @param afqcn
 * @parma argument_list
 * @return
 */
ast* ast_new_new_instance(ast* afqcn, ast* argument_list);

#endif // !SIGNAL_AST_AST_NEW_FACTOR_H
