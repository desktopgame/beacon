#pragma once
#ifndef BEACON_AST_AST_H
#define BEACON_AST_AST_H
#include <stdint.h>
#include <stdbool.h>
#include "access_level.h"
#include "modifier_type.h"
#include "constructor_chain_type.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "operator_type.h"
/**
 * AST(AbstractSourceTree) の種類を表すタグです.
 */
typedef enum ast_tag {
	AST_ROOT_T,
	AST_BLANK_T,
	AST_INJECT_JNI_VALUE_T,
	//+ - * / %
	AST_ADD_T,
	AST_SUB_T,
	AST_MUL_T,
	AST_DIV_T,
	AST_MOD_T,
	AST_LSHIFT_T,
	AST_RSHIFT_T,
	//| ||
	AST_BIT_OR_T,
	AST_LOGIC_OR_T,
	//& &&
	AST_BIT_AND_T,
	AST_LOGIC_AND_T,
	AST_EXC_OR_T,
	AST_CHILDA_T,
	//= += -= *= /= %=
	AST_AS_TSIGN_T,
	AST_ADD_ASSIGN_T,
	AST_SUB_ASSIGN_T,
	AST_MUL_ASSIGN_T,
	AST_DIV_ASSIGN_T,
	AST_MOD_ASSIGN_T,
	AST_OR_ASSIGN_T,
	AST_AND_ASSIGN_T,
	AST_EXC_OR_ASSIGN_T,
	AST_LSHIFT_ASSIGN_T,
	AST_RSHIFT_ASSIGN_T,
	//== !=
	AST_EQUAL_T,
	AST_NOT_TEQUAL_T,
	//> >= < <=
	AST_GT_T,
	AST_GE_T,
	AST_LT_T,
	AST_LE_T,
	//a is b
	AST_INSTANCEOF_T,
	//! -
	AST_NOT_T,
	AST_POS_T,
	AST_NEG_T,
	//() (...)
	AST_OP_CALL_T,
	//int double
	AST_INT_T,
	AST_DOUBLE_T,
	AST_CHAR_T,
	AST_STRING_T,
	AST_VARIABLE_T,
	AST_INFERENCED_TYPE_INIT_T,
	AST_CALL_T,
	AST_INVOKE_T,
	AST_SUBSCRIPT_ACCESS_T,
	AST_RETURN_T,
	AST_RETURN_EMPTY_T,
	AST_THIS_T,
	AST_SUPER_T,
	AST_NEW_INSTANCE_T,

	AST_FIELD_ACCESS_T,
	AST_STATIC_FIELD_ACCESS_T,

	AST_IDENTIFIER_T,
	AST_IDENTIFIER_LIST_T,
	//AST_TYPENAME_T,

	//AST_VARIABLE_T_decl,

	AST_NAMESPACE_DECL_T,
	AST_NAMESPACE_BODY_T,
	AST_NAMESPACE_MEMBER_DECL_T,
	AST_NAMESPACE_MEMBER_DECL_LIST_T,
	AST_NAMESPACE_PATH_T,
	AST_NAMESPACE_PATH_LIST_T,

	AST_IMPORT_DECL_T,
	AST_IMPORT_DECL_LIST_T,
	AST_IMPORT_PATH_T,

	AST_CLASS_DECL_UNIT_T,
	//ast_class_decl_list,
	AST_ABSTRACT_CLASS_DECL_T,
	AST_CLASS_DECL_T,
	AST_ENUM_DECL_T,
	AST_INTERFACE_DECL,
	AST_CLASS_SUPER_T,

	AST_ACCESS_LEVEL_T,
	AST_ACCESS_MEMBER_LIST_T,
	AST_ACCESS_MEMBER_TREE_T,

	AST_MEMBER_DECL_T,
	AST_MEMBER_DECL_LIST_T,

	AST_OPERATOR_OVERLOAD_T,

	AST_FIELD_DECL_T,
	AST_FIELD_TYPE_NAME_T,
	AST_FIELD_ACCESS_NAME_T,

	AST_PROP_SET_T,
	AST_PROP_GET_T,
	AST_PROP_DECL_T,

	AST_MOD_Tifier_list,
	AST_MOD_Tifier,

	AST_FUNCTION_DECL_T,
	AST_FUNCTION_NAME_T,
	AST_FUNCTION_RETURN_NAME_T,

	AST_METHOD_DECL_T,
	AST_METHOD_NAME_T,
	AST_METHOD_RETURN_NAME_T,

	AST_CONSTRUCTOR_DECL_T,
	AST_CONSTRUCTOR_CHAIN_T,
	AST_CONSTRUCTOR_CHAIN_THIS_T,
	AST_CONSTRUCTOR_CHAIN_SUPER_T,
	AST_EXPLICIT_BIOPERATOR_T,
	AST_EXPLICIT_UOPERATOR_T,

	AST_TRUE_T,
	AST_FALSE_T,
	AST_NULL_T,
	AST_AS_T,

	AST_SCOPE_T,
	AST_STMT_T,
	AST_WHILE_T,
	AST_BREAK_T,
	AST_CONTINUE_T,
	AST_YIELD_RETURN_T,
	AST_YIELD_BREAK_T,
	//
	//call(); 
	//a.invoke();
	//のような、式によってのみ構成される文(ステートメント)
	//を特別にプロセスと呼称します。
	//
	AST_PROC_T,
	AST_STMT_LIST_T,
	AST_NAME_REFERENCE_T,
	AST_TYPENAME_T,
	AST_TYPENAME_LIST_T,
	AST_STMT_VARIABLE_DECL_T,
	AST_STMT_VARIABLE_INIT_T,
	AST_STMT_DEFER_T,

	AST_STMT_TRY_T,
	AST_STMT_CATCH_T,
	AST_STMT_CATCH_LIST_T,
	AST_STMT_THROW_T,

	AST_STMT_ASSERT_T,

	AST_PARAMETER_T,
	AST_PARAMETER_TYPE_NAME_T,
	AST_PARAMETER_ACCESS_NAME_T,
	AST_PARAMETER_LIST_T,

	AST_ARGUMENT_T,
	AST_ARGUMENT_LIST_T,

	AST_FQCN_T,
	AST_FQCN_CLASS_NAME_T,
	AST_FQCN_PART_T,
	AST_FQCN_PART_LIST_T,

	AST_PARAMETERIZED_TYPENAME_T,
	AST_TYPE_PARAMETER_T,
	AST_TYPE_IN_PARAMETER_T,
	AST_TYPE_OUT_PARAMETER_T,
	AST_TYPE_PARAMETER_LIST_T,

	AST_TYPE_PARAMETER_RULE_LIST_T,

	AST_STATIC_INVOKE_T,
	//stmt
	AST_IF_T,
	AST_ELSE_T,
	AST_IF_ELSE_T,
	AST_IF_ELIF_LIST_T,
	AST_IF_ELIF_LIST_ELSE_T,
	AST_ELIF_LIST_T,
	AST_ELIF_T,
} ast_tag;

/**
 * ソースコード中の要素を表します.
 */
typedef struct ast {
	union {
		int int_value;
		double double_value;
		char char_value;
		StringView stringv_value;
		access_level access_value;
		modifier_type modifier_value;
		operator_type operator_value;
	} u;
	ast_tag tag;
	//uint32_t child_count;
	uint32_t lineno;
	Vector* vchildren;
	//list* children;
} ast;

/**
 * 現在のコンパイラに AST を追加します.
 * @param self
 */
void CompileEntryAST(ast* self);

/**
 * 指定のタグで子要素を持たない AST を作成します.
 */
#define ast_new(tag) (MallocAST(tag, __FILE__, __LINE__))

/**
 * 指定のタグで子要素を持たない AST を作成します.
 * @param tag
 * @param filename
 * @param lineno
 */
ast* MallocAST(ast_tag tag, const char* filename, int lineno);

/**
 * 名前空間の一節(. ~~~ .)を表す要素を作成します.
 * @param namev
 * @return
 */
ast* NewASTNamespacePath(StringView namev);

/**
 * 二つの名前空間を連結します.
 * @param aforward
 * @param namev
 * @return
 */
ast* NewASTNamespacePathList(ast* aforward, StringView namev);

/**
 * インポート先のファイルを表す要素を作成します.
 * @param astr
 * @return
 */
ast* NewASTImportPath(ast* astr);

/**
 * インポート宣言を表す要素を作成します.
 * @param aimport_path
 * @return
 */
ast* NewASTImportDecl(ast* aimport_path);

/**
 * インポートの一覧を表す要素を作成します.
 * @param aimport
 * @param aimport_list
 * @return
 */
ast* NewASTImportDeclList(ast* aimport, ast* aimport_list);

/**
 * スコープ({ ... }) を表す要素を作成します.
 * @param astmt_list
 * @return
 */
ast* NewASTScope(ast* astmt_list);

/**
 * 空のスコープを表す要素を作成します.
 * @return
 */
ast* NewASTScopeEmpty();

/**
 * 空の要素を作成します.
 */
ast* NewASTBlank();

/**
 * 識別子を表す要素を作成します.
 * @param strv
 * @return
 */
ast* NewASTIdentifier(StringView strv);

/**
 * 識別子のリストを表す要素を作成します.
 * @param strv
 * @param aident_list
 * @return
 */
ast* NewASTIdentifierList(StringView strv, ast* aident_list);

/**
 * 計算可能な要素だけで構成される文を作成します.
 * @param aexpr
 * @return
 */
ast* NewASTProc(ast* aexpr);

/**
 * self に child を子要素として追加します.
 * @param self
 * @param achild
 */
ast* PushAST(ast* self, ast* achild);

/** 
 * 指定位置の子要素を返します.
 * @param self
 * @param index
 */
ast* AtAST(ast* self, int index);

/**
 * 最初の子要素を返します.
 * @param self
 * @return
 */
ast* FirstAST(ast* self);

/**
 * 二番目の子要素を返します.
 * @param self
 * @return
 */
ast* SecondAST(ast* self);

/**
 * 指定の AST とその子要素を全て開放します.
 * @param self
 */
void DeleteAST(ast* self);

/**
 * 指定の要素が空なら true.
 * @param self
 * @return
 */
bool IsBlankAST(ast* self);

/**
 * 指定の要素がアクセスレベルなら true.
 * @param self
 * @return
 */
bool IsAccessAST(ast* self);

/**
 * 指定の要素が修飾子なら true.
 * @param self
 * @return
 */
bool IsModifierAST(ast* self);

/**
 * 指定の要素がステートメントなら true.
 * @param self
 * @return
 */
bool IsStmtAST(ast* self);

/**
 * 指定の要素がアクセスレベルを表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
access_level ASTCastToAccess(ast* self);

/**
 * 指定の要素が修飾子を表す要素なら列挙型に変換します.
 * @param self
 * @param error
 * @return
 */
modifier_type ASTCastToModifier(ast* self, bool* error);

/**
 * 指定の要素が連鎖を表す要素なら列挙型に変換します.
 * @param self
 * @return
 */
constructor_chain_type ASTCastToChainType(ast* self);
#endif // !SIGNAL_AST_AST_H
