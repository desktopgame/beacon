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
 * @param aNamespacepath
 * @param abody
 * @return
 */
AST* NewASTNamespaceDecl(AST* aNamespacepath, AST* abody);

/**
 * 名前空間の内側に定義された名前空間を表す要素を作成します.
 * @param aNamespacepath
 * @param abody
 * @return
 */
AST* NewASTNamespaceNamespaceDecl(AST* aNamespacepath, AST* abody);

/**
 * 名前空間の内側に含めることが出来る定義の一覧を作成します.
 * @param aforward
 * @param alist
 * @return
 */
AST* NewASTNamespaceMemberDeclList(AST* aforward, AST* alist);

/**
 * 抽象クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 */
AST* NewASTAbstractClassDecl(AST* aclass_name, AST* aextend_list, AST* amember_list);

/**
 * クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 * @return
 */
AST* NewASTClassDecl(AST* aclass_name, AST* aextend_list, AST* amember_list);

/**
 * インターフェース宣言を表す要素を作成します.
 * @param ainterface_name
 * @param asuper_interface_list
 * @param amember_list
 * @return
 */
AST* NewASTInterfaceDecl(AST* ainterface_name, AST* asuper_interface_list, AST* amember_list);

/**
 * 列挙宣言を表す要素を作成します.
 * @param aenum_namev
 * @param aident_list
 * @return
 */
AST* NewASTEnumDecl(StringView enum_namev, AST* aident_list);

/**
 * スーパークラスを表す要素を作成します.
 * @param fqcn
 * @return
 */
AST* NewASTSuperclass(AST* afqcn);

/**
 * "アクセス修飾子とメンバー一覧のセット" のリストを返します.
 * @param amember_tree
 * @param amember_list
 * @return
 */
AST* NewASTAccessMemberTree(AST* member_tree, AST* member_list);

/**
 * アクセス修飾子とメンバーの一覧をセットにして返します.
 * @param level
 * @param amember_list
 * @return
 */
AST* NewASTAccessMemberList(AccessLevel level, AST* amember_list);

/**
 * アクセスレベルを表す要素を作成します.
 * @param level
 * @return
 */
AST* NewASTAccess(AccessLevel level);

/**
 * 修飾子の一覧を表す要素を作成します.
 * @param amod
 * @param amod_list
 * @return
 */
AST* NewASTModifierList(AST* amod, AST* amod_list);

/**
 * 修飾子を表す要素を作成します.
 * @param type
 * @return
 */
AST* NewASTModifier(ModifierType type);

/**
 * メンバーを表す要素を作成します.
 * @param mem
 * @return
 */
AST* NewASTMemberDecl(AST* amem);

/**
 * メンバーを表す要素を作成します.
 * @param amember_list
 * @param amember
 * @param
 */
AST* NewASTMemberDeclList(AST* amember_list, AST* amember);

/**
 * フィールド宣言を表す要素を作成します.
 * @param amodifier
 * @param aGetTypeName
 * @param field_namev
 * @param afact
 * @return
 */
AST* NewASTFieldDecl(AST* amodifier, AST* aGetTypeName, StringView field_namev, AST* afact);

/**
 * 関数宣言を表す要素を作成します.
 * @param function_namev
 * @param atypeparams
 * @parma aparameter_list
 * @param abody
 * @param areturn_type
 */
AST* NewASTFunctionDecl(StringView function_namev, AST* atypeparams, AST* aparameter_list, AST* abody, AST* areturn_type);

/**
 * 引数のない関数宣言を表す要素を作成します.
 * @param function_namev
 * @param atypeparams
 * @param abody
 * @param areturn_name
 * @return
 */
AST* NewASTFunctionDeclEmptyParams(StringView function_namev, AST* atypeparams, AST* abody, AST* areturn_type);

/**
 * メソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_namev
 * @param atype_parameter
 * @param aparameter_list
 * @param abody
 * @param areturn_GetTypeName
 * @return
 */
AST* NewASTMethodDecl(AST* amodifier, StringView func_namev, AST* atype_parameter, AST* aparameter_list, AST* abody, AST* areturn_type);

/**
 * 引数のないメソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_namev
 * @param atype_parameter
 * @param abody
 * @param areturn_GetTypeName
 * @return
 */
AST* NewASTMethodDeclEmptyParams(AST* amodifier, StringView func_namev, AST* atype_parameter, AST* abody, AST* areturn_type);

/**
 * コンストラクタ宣言を表す要素を作成します.
 * @param aparameter_list
 * @param aconstructor_chain
 * @param abody
 * @return
 */
AST* NewASTConstructorDecl(AST* aparameter_list, AST* aconstructor_chain, AST* abody);

/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @param chain
 * @param aargument_list
 * @return
 */
AST* NewASTConstructorChain(ConstructorChainType chain_type, AST* aargument_list);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_namev
 * @return
 */
AST* NewASTParameter(AST* atypename, StringView parameter_access_namev);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_namev
 * @param aparameter_list
 * @return
 */
AST* NewASTParameterList(AST* atypename, StringView parameter_access_namev, AST* aparameter_list);

/**
 * クラスが実装するインターフェイスの一覧として使用される、
 * 型名の一覧を作成します.
 * @param atypename
 * @param atypename_list
 * @return
 */
AST* NewASTTypenameList(AST* atypename, AST* atypename_list);

/**
 * X::Y::C や C を型名でラップします.
 * @param afqcn
 * @param atype_args
 * @return
 */
AST* NewASTTypename(AST* fqcn, AST* atype_args);

/**
 * T や K V などの要素を作成します.
 * @param namev
 * @param arule_list
 * @return
 */
AST* NewASTTypeParameter(StringView namev, AST* arule_list);
AST* NewASTTypeInParameter(StringView namev, AST* arule_list);
AST* NewASTTypeOutParameter(StringView namev, AST* arule_list);

/** 
 * T や K V の要素のリストを作成します.
 * @param aparam
 * @param alist
 * @return
 */
AST* NewASTTypeParameterList(AST* aparam, AST* alist);

/**
 * Name<T> や Name<K, V> のような要素を作成します.
 * @param name
 * @param aparams
 * @return
 */
AST* NewASTParameterizedTypename(StringView namev, AST* aparams);

/**
 * 型制約の一覧を表す要素を作成します.
 * @param arule_list
 * @return
 */
AST* NewASTTypeParameterRuleList(AST* arule_list);

/**
 * 演算子オーバーロードを表す要素を作成します.
 * @param type
 * @param aparam_list
 * @param abody
 * @param areturn
 */
AST* NewASTOperatorOverload(OperatorType type, AST* aparam_list, AST* abody, AST* areturn);

/**
 * プロパティの set部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @areturn
 */
AST* NewASTPropSet(AST* aacess, AST* abody);

/**
 * プロパティの get部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @return
 */
AST* NewASTPropGet(AST* aacess, AST* abody);

/**
 * プロパティ宣言を作成します.
 * @param amodifier
 * @param atypename
 * @param namev
 * @param aset
 * @param aget
 */
AST* NewASTPropDecl(AST* amodifier, AST* atypename, StringView namev, AST* aset, AST* aget);
#endif // !SIGNAL_AST_AST_NEW_DECL_H
