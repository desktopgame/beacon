#pragma once
#ifndef SIGNAL_AST_AST_NEW_OPERATOR_H
#define SIGNAL_AST_AST_NEW_OPERATOR_H
#include "ast.h"
//typedef struct ast { } ast;
/**
* 加算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_add(ast* l, ast* r);

/**
* 減算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_sub(ast* l, ast* r);

/**
* 乗算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_mul(ast* l, ast* r);

/**
* 除算を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_div(ast* l, ast* r);

/**
* 剰余を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_mod(ast* l, ast* r);

/**
 * 代入を表す要素を作成します.
 * @param l
 * @param r
 * @retrun
 */
ast* ast_new_assign(ast* l, ast* r);

/**
 * 加算代入を表す要素を作成します.
 * @param l
 * @param r
 * @retrun
 */
ast* ast_new_add_assign(ast* l, ast* r);

/**
 * 減算代入を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_sub_assign(ast* l, ast* r);

/**
 * 乗算代入を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_mul_assign(ast* l, ast* r);

/**
 * 除算代入を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_div_assign(ast* l, ast* r);

/**
 * 剰余代入を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_mod_assign(ast* l, ast* r);

/**
 * ビット演算における OR を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_bit_or(ast* l, ast* r);

/**
 * 論理演算における OR を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_logic_or(ast* l, ast* r);

/**
* ビット演算における AND を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_bit_and(ast* l, ast* r);

/**
* 論理演算における AND を表す要素を作成します.
* @param l
* @param r
* @return
*/
ast* ast_new_logic_and(ast* l, ast* r);

/**
 * 比較演算における == を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_equal(ast* l, ast* r);

/**
 * 比較演算における != を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_notequal(ast* l, ast* r);

/**
 * 比較演算における > を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_gt(ast* l, ast* r);

/**
 * 比較演算における >= を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_ge(ast* l, ast* r);

/**
 * 比較演算における < を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_lt(ast* l, ast* r);

/**
 * 比較演算における <= を表す要素を作成します.
 * @param l
 * @param r
 * @return
 */
ast* ast_new_le(ast* l, ast* r);

/**
 * 単項否定演算子 ! を表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_not(ast* a);

/**
 * 単項マイナス演算子 - を表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_neg(ast* a);
#endif // !SIGNAL_AST_AST_NEW_OPERATOR_H
