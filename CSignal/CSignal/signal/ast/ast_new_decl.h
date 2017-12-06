#pragma once
#ifndef SIGNAL_AST_AST_NEW_DECL_H
#define SIGNAL_AST_AST_NEW_DECL_H
#include "ast.h"
#include "constructor_chain_type.h"
#include "modifier_type.h"

/**
 * クラス宣言を表す要素を作成します.
 * @param class_name
 * @param super_class
 * @param member_list
 * @return
 */
ast* ast_new_class_decl(char* class_name, ast* super_class, ast* member_list);

/**
 * スーパークラスを表す要素を作成します.
 * @param class_name
 * @return
 */
ast* ast_new_superclass(char* class_name);

/**
 * 修飾子を表す要素を作成します.
 * @param type
 * @return
 */
ast* ast_new_modifier(modifier_type type);

/**
 * 修飾子を表す要素を作成します.
 * @param modifier_list
 * @parma modifier_type
 * @return
 */
ast* ast_new_modifier_list(ast* modifier_list, modifier_type type);

/**
 * メンバーを表す要素を作成します.
 * @param mem
 * @return
 */
ast* ast_new_member_decl(ast* mem);

/**
 * メンバーを表す要素を作成します.
 * @param mem
 * @param
 */
ast* ast_new_member_decl_list(ast* mem, ast* member_list);

/**
 * フィールド宣言を表す要素を作成します.
 * @param type_name
 * @param field_name
 * @return
 */
ast* ast_new_field_decl(char* type_name, char* field_name);

/**
 * 関数宣言を表す要素を作成します.
 * @param func_name
 * @param parameter_list
 * @param body
 * @param return_type_name
 * @return
 */
ast* ast_new_function_decl(char* func_name, ast* parameter_list, ast* body, char* return_type_name);

/**
 * 関数宣言を表す要素を作成します.
 * @param func_name
 * @param body
 * @param return_type_name
 * @return
 */
ast* ast_new_function_decl_empty_params(char* func_name, ast* body, char* return_type_name);

/**
 * コンストラクタ宣言を表す要素を作成します.
 * @param parameter_list
 * @param constructor_chain
 * @param body
 * @return
 */
ast* ast_new_constructor_decl(ast* parameter_list, ast* constructor_chain, ast* body);

/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @param chain
 * @param argument_list
 * @return
 */
ast* ast_new_constructor_chain(constructor_chain_type chain_type, ast* argument_list);

/**
 * 仮引数を表す要素を作成します.
 * @param parameter_type_name
 * @param parameter_access_name
 * @return
 */
ast* ast_new_parameter(char* parameter_type_name, char* parameter_access_name);

/**
 * 仮引数を表す要素を作成します.
 * @param parameter_type_name
 * @param parameter_access_name
 * @param parameter_list
 * @return
 */
ast* ast_new_parameter_list(char* parameter_type_name, char* parameter_access_name, ast* parameter_list);

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
#endif // !SIGNAL_AST_AST_NEW_DECL_H
