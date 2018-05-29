#pragma once
#ifndef BEACON_AST_AST_NEW_DECL_H
#define BEACON_AST_AST_NEW_DECL_H
#include "ast.h"
#include "constructor_chain_type.h"
#include "modifier_type.h"
#include "access_level.h"

/**
 * 名前空間を表す要素を作成します.
 * @param namespace_path
 * @param body
 * @return
 */
ast* ast_new_namespace_decl(ast* namespace_path, ast* body);

/**
 * 名前空間の内側に定義された名前空間を表す要素を作成します.
 * @param namespace_path
 * @param body
 * @return
 */
ast* ast_new_namespace_namespace_decl(ast* namespace_path, ast* body);

/**
 * 名前空間の内側に含めることが出来る定義の一覧を作成します.
 * @param forward
 * @param list
 * @return
 */
ast* ast_new_namespace_member_decl_list(ast* forward, ast* list);

/**
 * 抽象クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param extend_list
 * @param member_list
 */
ast* ast_new_abstract_class_decl(ast* aclass_name, ast* extend_list, ast* member_list);

/**
 * クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param extend_list
 * @param member_list
 * @return
 */
ast* ast_new_class_decl(ast* aclass_name, ast* extend_list, ast* member_list);

/**
 * インターフェース宣言を表す要素を作成します.
 * @param ainterface_name
 * @param super_interface_list
 * @param member_list
 * @return
 */
ast* ast_new_interface_decl(ast* ainterface_name, ast* super_interface_list, ast* member_list);

/**
 * 列挙宣言を表す要素を作成します.
 * @param enum_name
 * @param ident_list
 * @return
 */
ast* ast_new_enum_decl(char* enum_name, ast* ident_list);

/**
 * スーパークラスを表す要素を作成します.
 * @param fqcn
 * @return
 */
ast* ast_new_superclass(ast* fqcn);

/**
 * "アクセス修飾子とメンバー一覧のセット" のリストを返します.
 * @param member_tree
 * @param member_list
 * @return
 */
ast* ast_new_access_member_tree(ast* member_tree, ast* member_list);

/**
 * アクセス修飾子とメンバーの一覧をセットにして返します.
 * @param level
 * @param member_list
 * @return
 */
ast* ast_new_access_member_list(access_level level, ast* member_list);

/**
 * アクセスレベルを表す要素を作成します.
 * @param level
 * @return
 */
ast* ast_new_access(access_level level);

/**
 * 修飾子を表す要素を作成します.
 * @param type
 * @return
 */
ast* ast_new_modifier(modifier_type type);

/**
 * メンバーを表す要素を作成します.
 * @param mem
 * @return
 */
ast* ast_new_member_decl(ast* mem);

/**
 * メンバーを表す要素を作成します.
 * @param member_list
 * @param member
 * @param
 */
ast* ast_new_member_decl_list(ast* member_list, ast* member);

/**
 * フィールド宣言を表す要素を作成します.
 * @param amodifier
 * @param type_name
 * @param field_name
 * @return
 */
ast* ast_new_field_decl(ast* amodifier, ast* type_name, char* field_name);

/**
 * 関数宣言を表す要素を作成します.
 * @param function_name
 * @parma parameter_list
 * @param body
 * @param return_type
 */
ast* ast_new_function_decl(char* function_name, ast* parameter_list, ast* body, ast* return_type);

/**
 * 引数のない関数宣言を表す要素を作成します.
 * @param function_name
 * @param body
 * @param return_name
 * @return
 */
ast* ast_new_function_decl_empty_params(char* function_name, ast* body, ast* return_type);

/**
 * メソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_name
 * @param atype_parameter
 * @param parameter_list
 * @param body
 * @param return_type_name
 * @return
 */
ast* ast_new_method_decl(ast* amodifier, char* func_name, ast* atype_parameter, ast* parameter_list, ast* body, ast* return_type);

/**
 * 引数のないメソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_name
 * @param atype_parameter
 * @param body
 * @param return_type_name
 * @return
 */
ast* ast_new_method_decl_empty_params(ast* amodifier, char* func_name, ast* atype_parameter, ast* body, ast* return_type);

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
 * @param atypename
 * @param parameter_access_name
 * @return
 */
ast* ast_new_parameter(ast* atypename, char* parameter_access_name);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_name
 * @param parameter_list
 * @return
 */
ast* ast_new_parameter_list(ast* atypename, char* parameter_access_name, ast* parameter_list);

/**
 * クラスが実装するインターフェイスの一覧として使用される、
 * 型名の一覧を作成します.
 * @param atypename
 * @param typename_list
 * @return
 */
ast* ast_new_typename_list(ast* atypename, ast* typename_list);

/**
 * X::Y::C や C を型名でラップします.
 * @param fqcn
 * @param atype_args
 * @return
 */
ast* ast_new_typename(ast* fqcn, ast* atype_args);

/**
 * T や K V などの要素を作成します.
 * @param name
 * @param arule_list
 * @return
 */
ast* ast_new_type_parameter(char* name, ast* arule_list);
ast* ast_new_type_in_parameter(char* name, ast* arule_list);
ast* ast_new_type_out_parameter(char* name, ast* arule_list);

/** 
 * T や K V の要素のリストを作成します.
 * @param aparam
 * @param alist
 * @return
 */
ast* ast_new_type_parameter_list(ast* aparam, ast* alist);

/**
 * Name<T> や Name<K, V> のような要素を作成します.
 * @param name
 * @param aparams
 * @return
 */
ast * ast_new_parameterized_typename(char* name, ast* aparams);

/**
 * 型制約の一覧を表す要素を作成します.
 * @param arule_list
 * @return
 */
ast* ast_new_type_parameter_rule_list(ast* arule_list);
#endif // !SIGNAL_AST_AST_NEW_DECL_H
