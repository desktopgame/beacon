#pragma once
#ifndef BEACON_AST_AST_NEW_DECL_H
#define BEACON_AST_AST_NEW_DECL_H
#include "ast.h"
#include "constructor_chain_type.h"
#include "modifier_type.h"
#include "access_level.h"
#include "operator_type.h"

/**
 * 名前空間を表す要素を作成します.
 * @param anamespace_path
 * @param abody
 * @return
 */
ast* ast_new_namespace_decl(ast* anamespace_path, ast* abody);

/**
 * 名前空間の内側に定義された名前空間を表す要素を作成します.
 * @param anamespace_path
 * @param abody
 * @return
 */
ast* ast_new_namespace_namespace_decl(ast* anamespace_path, ast* abody);

/**
 * 名前空間の内側に含めることが出来る定義の一覧を作成します.
 * @param aforward
 * @param alist
 * @return
 */
ast* ast_new_namespace_member_decl_list(ast* aforward, ast* alist);

/**
 * 抽象クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 */
ast* ast_new_abstract_class_decl(ast* aclass_name, ast* aextend_list, ast* amember_list);

/**
 * クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 * @return
 */
ast* ast_new_class_decl(ast* aclass_name, ast* aextend_list, ast* amember_list);

/**
 * インターフェース宣言を表す要素を作成します.
 * @param ainterface_name
 * @param asuper_interface_list
 * @param amember_list
 * @return
 */
ast* ast_new_interface_decl(ast* ainterface_name, ast* asuper_interface_list, ast* amember_list);

/**
 * 列挙宣言を表す要素を作成します.
 * @param aenum_namev
 * @param aident_list
 * @return
 */
ast* ast_new_enum_decl(string_view enum_namev, ast* aident_list);

/**
 * スーパークラスを表す要素を作成します.
 * @param fqcn
 * @return
 */
ast* ast_new_superclass(ast* afqcn);

/**
 * "アクセス修飾子とメンバー一覧のセット" のリストを返します.
 * @param amember_tree
 * @param amember_list
 * @return
 */
ast* ast_new_access_member_tree(ast* member_tree, ast* member_list);

/**
 * アクセス修飾子とメンバーの一覧をセットにして返します.
 * @param level
 * @param amember_list
 * @return
 */
ast* ast_new_access_member_list(access_level level, ast* amember_list);

/**
 * アクセスレベルを表す要素を作成します.
 * @param level
 * @return
 */
ast* ast_new_access(access_level level);

/**
 * 修飾子の一覧を表す要素を作成します.
 * @param amod
 * @param amod_list
 * @return
 */
ast* ast_new_modifier_list(ast* amod, ast* amod_list);

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
ast* ast_new_member_decl(ast* amem);

/**
 * メンバーを表す要素を作成します.
 * @param amember_list
 * @param amember
 * @param
 */
ast* ast_new_member_decl_list(ast* amember_list, ast* amember);

/**
 * フィールド宣言を表す要素を作成します.
 * @param amodifier
 * @param atype_name
 * @param field_namev
 * @param afact
 * @return
 */
ast* ast_new_field_decl(ast* amodifier, ast* atype_name, string_view field_namev, ast* afact);

/**
 * 関数宣言を表す要素を作成します.
 * @param function_namev
 * @param atypeparams
 * @parma aparameter_list
 * @param abody
 * @param areturn_type
 */
ast* ast_new_function_decl(string_view function_namev, ast* atypeparams, ast* aparameter_list, ast* abody, ast* areturn_type);

/**
 * 引数のない関数宣言を表す要素を作成します.
 * @param function_namev
 * @param atypeparams
 * @param abody
 * @param areturn_name
 * @return
 */
ast* ast_new_function_decl_empty_params(string_view function_namev, ast* atypeparams, ast* abody, ast* areturn_type);

/**
 * メソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_namev
 * @param atype_parameter
 * @param aparameter_list
 * @param abody
 * @param areturn_type_name
 * @return
 */
ast* ast_new_method_decl(ast* amodifier, string_view func_namev, ast* atype_parameter, ast* aparameter_list, ast* abody, ast* areturn_type);

/**
 * 引数のないメソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_namev
 * @param atype_parameter
 * @param abody
 * @param areturn_type_name
 * @return
 */
ast* ast_new_method_decl_empty_params(ast* amodifier, string_view func_namev, ast* atype_parameter, ast* abody, ast* areturn_type);

/**
 * コンストラクタ宣言を表す要素を作成します.
 * @param aparameter_list
 * @param aconstructor_chain
 * @param abody
 * @return
 */
ast* ast_new_constructor_decl(ast* aparameter_list, ast* aconstructor_chain, ast* abody);

/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @param chain
 * @param aargument_list
 * @return
 */
ast* ast_new_constructor_chain(constructor_chain_type chain_type, ast* aargument_list);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_namev
 * @return
 */
ast* ast_new_parameter(ast* atypename, string_view parameter_access_namev);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_namev
 * @param aparameter_list
 * @return
 */
ast* ast_new_parameter_list(ast* atypename, string_view parameter_access_namev, ast* aparameter_list);

/**
 * クラスが実装するインターフェイスの一覧として使用される、
 * 型名の一覧を作成します.
 * @param atypename
 * @param atypename_list
 * @return
 */
ast* ast_new_typename_list(ast* atypename, ast* atypename_list);

/**
 * X::Y::C や C を型名でラップします.
 * @param afqcn
 * @param atype_args
 * @return
 */
ast* ast_new_typename(ast* fqcn, ast* atype_args);

/**
 * T や K V などの要素を作成します.
 * @param namev
 * @param arule_list
 * @return
 */
ast* ast_new_type_parameter(string_view namev, ast* arule_list);
ast* ast_new_type_in_parameter(string_view namev, ast* arule_list);
ast* ast_new_type_out_parameter(string_view namev, ast* arule_list);

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
ast * ast_new_parameterized_typename(string_view namev, ast* aparams);

/**
 * 型制約の一覧を表す要素を作成します.
 * @param arule_list
 * @return
 */
ast* ast_new_type_parameter_rule_list(ast* arule_list);

/**
 * 演算子オーバーロードを表す要素を作成します.
 * @param type
 * @param aparam_list
 * @param abody
 * @param areturn
 */
ast* ast_new_operator_overload(operator_type type, ast* aparam_list, ast* abody, ast* areturn);

/**
 * プロパティの set部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @areturn
 */
ast* ast_new_prop_set(ast* aacess, ast* abody);

/**
 * プロパティの get部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @return
 */
ast* ast_new_prop_get(ast* aacess, ast* abody);

/**
 * プロパティ宣言を作成します.
 * @param amodifier
 * @param atypename
 * @param namev
 * @param aset
 * @param aget
 */
ast* ast_new_prop_decl(ast* amodifier, ast* atypename, string_view namev, ast* aset, ast* aget);
#endif // !SIGNAL_AST_AST_NEW_DECL_H
