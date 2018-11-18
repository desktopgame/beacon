#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static bc_AST* ast_new_field_GetTypeName(StringView GetTypeNamev);
static bc_AST* NewASTFieldAccess_name(StringView field_namev);
static bc_AST* ast_new_function_name(StringView func_namev);
static bc_AST* ast_new_method_name(StringView func_namev);
static bc_AST* ast_new_method_return_name(StringView return_GetTypeNamev);
static bc_AST* NewASTParameter_GetTypeName(StringView GetTypeNamev);
static bc_AST* NewASTParameter_access_name(StringView parameter_namev);
static bc_AST* NewASTClassDeclImpl(bc_AST* aclass_name, bc_AST* aextend_list, bc_AST* amember_list, bc_ASTTag tag);

bc_AST* bc_NewASTNamespaceDecl(bc_AST* anamespace_path, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_NAMESPACE_DECL_T);
	bc_PushAST(ret, anamespace_path);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* bc_NewASTNamespaceNamespaceDecl(bc_AST* anamespace_path, bc_AST* abody) {
	return bc_NewASTNamespaceDecl(anamespace_path, abody);
}

bc_AST* bc_NewASTNamespaceMemberDeclList(bc_AST* aforward, bc_AST* alist) {
	bc_AST* ret = bc_NewAST(AST_NAMESPACE_MEMBER_DECL_LIST_T);
	bc_PushAST(ret, aforward);
	bc_PushAST(ret, alist);
	return ret;
}

bc_AST* bc_NewASTAbstractClassDecl(bc_AST* aclass_name, bc_AST* aextend_list, bc_AST* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_ABSTRACT_CLASS_DECL_T);
}

bc_AST* bc_NewASTClassDecl(bc_AST* aclass_name, bc_AST* aextend_list, bc_AST* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_CLASS_DECL_T);
}

bc_AST* bc_NewASTInterfaceDecl(bc_AST* ainterface_name, bc_AST* asuper_interface_list, bc_AST* amember_list) {
	bc_AST* ret = bc_NewAST(AST_INTERFACE_DECL);
	bc_PushAST(ret, ainterface_name);
	bc_PushAST(ret, asuper_interface_list);
	bc_PushAST(ret, amember_list);
	return ret;
}

bc_AST* bc_NewASTEnumDecl(StringView enum_name, bc_AST* aident_list) {
	bc_AST* ret = bc_NewAST(AST_ENUM_DECL_T);
	ret->Attr.StringVValue = enum_name;
	bc_PushAST(ret, aident_list);
	return ret;
}

bc_AST* bc_NewASTSuperclass(bc_AST* afqcn) {
	bc_AST* ret = bc_NewAST(AST_CLASS_SUPER_T);
	bc_PushAST(ret, afqcn);
	return ret;
}

bc_AST* bc_NewASTAccessMemberTree(bc_AST* amember_tree, bc_AST* amember_list) {
	bc_AST* ret = bc_NewAST(AST_ACCESS_MEMBER_TREE_T);
	bc_PushAST(ret, amember_tree);
	bc_PushAST(ret, amember_list);
	return ret;
}

bc_AST* bc_NewASTAccessMemberList(bc_AccessLevel level, bc_AST* amember_list) {
	bc_AST* ret = bc_NewAST(AST_ACCESS_MEMBER_LIST_T);
	bc_AST* a = bc_NewASTAccess(level);
	bc_PushAST(ret, a);
	bc_PushAST(ret, amember_list);
	return ret;
}

bc_AST* bc_NewASTAccess(bc_AccessLevel level) {
	bc_AST* ret = bc_NewAST(AST_ACCESS_LEVEL_T);
	ret->Attr.AccessValue = level;
	return ret;
}

bc_AST* bc_NewASTModifierList(bc_AST* amod, bc_AST* amod_list) {
	bc_AST* ret = bc_NewAST(AST_MOD_Tifier_list);
	bc_PushAST(ret, amod);
	bc_PushAST(ret, amod_list);
	return ret;
}

bc_AST* bc_NewASTModifier(bc_ModifierType type) {
	bc_AST* ret = bc_NewAST(AST_MOD_Tifier);
	ret->Attr.ModifierValue = type;
	return ret;
}

bc_AST* bc_NewASTMemberDecl(bc_AST* amem) {
	bc_AST* ret = bc_NewAST(AST_MEMBER_DECL_T);
	bc_PushAST(ret, amem);
	return ret;
}

bc_AST* bc_NewASTMemberDeclList(bc_AST* amember_list, bc_AST* amember) {
	bc_AST* ret = bc_NewAST(AST_MEMBER_DECL_LIST_T);
	bc_PushAST(ret, amember_list);
	bc_PushAST(ret, amember);
	return ret;
}

bc_AST* bc_NewASTFieldDecl(bc_AST* amodifier, bc_AST* atypename, StringView field_name, bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_FIELD_DECL_T);
	bc_PushAST(ret, amodifier);
	bc_PushAST(ret, atypename);
	bc_PushAST(ret, NewASTFieldAccess_name(field_name));
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* bc_NewASTFunctionDecl(StringView function_namev, bc_AST* atypeparams, bc_AST* aparameter_list, bc_AST* abody, bc_AST* areturn_type) {
	bc_AST* ret = bc_NewAST(AST_FUNCTION_DECL_T);
	bc_PushAST(ret, ast_new_function_name(function_namev));
	bc_PushAST(ret, atypeparams);
	bc_PushAST(ret, aparameter_list);
	bc_PushAST(ret, abody);
	bc_PushAST(ret, areturn_type);
	return ret;
}

bc_AST* bc_NewASTFunctionDeclEmptyParams(StringView function_name, bc_AST* atypeparams, bc_AST* abody, bc_AST* areturn_type) {
	return bc_NewASTFunctionDecl(function_name, atypeparams, bc_NewASTBlank(), abody, areturn_type);
}

bc_AST* bc_NewASTMethodDecl(bc_AST* amodifier, StringView func_name, bc_AST* atype_parameter, bc_AST* aparameter_list, bc_AST* abody, bc_AST* areturn_type) {
	bc_AST* ret = bc_NewAST(AST_METHOD_DECL_T);
	bc_PushAST(ret, amodifier);
	bc_PushAST(ret, ast_new_method_name(func_name));
	bc_PushAST(ret, atype_parameter);
	bc_PushAST(ret, aparameter_list);
	bc_PushAST(ret, abody);
	bc_PushAST(ret, areturn_type);
	return ret;
}

bc_AST* bc_NewASTMethodDeclEmptyParams(bc_AST* amodifier, StringView func_name, bc_AST* atype_parameter, bc_AST* abody, bc_AST* areturn_type) {
	return bc_NewASTMethodDecl(amodifier, func_name, atype_parameter, bc_NewASTBlank(), abody, areturn_type);
}

bc_AST* bc_NewASTConstructorDecl(bc_AST* aparameter_list, bc_AST* aconstructor_chain, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_CONSTRUCTOR_DECL_T);
	bc_PushAST(ret, aparameter_list);
	bc_PushAST(ret, aconstructor_chain);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* bc_NewASTConstructorChain(bc_ConstructorChainType chain_type, bc_AST* aargument_list) {
	bc_AST* ret = bc_NewAST(AST_CONSTRUCTOR_CHAIN_T);
	if (chain_type == CHAIN_TYPE_THIS_T) {
		bc_PushAST(ret, bc_NewAST(AST_CONSTRUCTOR_CHAIN_THIS_T));
	} else {
		bc_PushAST(ret, bc_NewAST(AST_CONSTRUCTOR_CHAIN_SUPER_T));
	}
	bc_PushAST(ret, aargument_list);
	return ret;
}

bc_AST* bc_NewASTParameter(bc_AST* atypename, StringView parameter_access_name) {
	bc_AST* ret = bc_NewAST(AST_PARAMETER_T);
	bc_PushAST(ret, atypename);
	bc_PushAST(ret, NewASTParameter_access_name(parameter_access_name));
	return ret;
}

bc_AST* bc_NewASTParameterList(bc_AST* atypename, StringView parameter_access_name, bc_AST* aparameter_list) {
	bc_AST* ret = bc_NewAST(AST_PARAMETER_LIST_T);
	bc_PushAST(ret, aparameter_list);
	bc_PushAST(ret, bc_NewASTParameter(atypename, parameter_access_name));
	return ret;
}

bc_AST* bc_NewASTTypenameList(bc_AST* atypename, bc_AST* atypename_list) {
	bc_AST* ret = bc_NewAST(AST_TYPENAME_LIST_T);
	bc_PushAST(ret, atypename_list);
	bc_PushAST(ret, atypename);
	return ret;
}

bc_AST* bc_NewASTTypename(bc_AST* afqcn, bc_AST* atype_args) {
	bc_AST* ret = bc_NewAST(AST_TYPENAME_T);
	bc_PushAST(ret, afqcn);
	bc_PushAST(ret, atype_args);
	return ret;
}

bc_AST* bc_NewASTTypeParameter(StringView name, bc_AST* arule_list) {
	bc_AST* ret = bc_NewAST(AST_TYPE_PARAMETER_T);
	ret->Attr.StringVValue = name;
	bc_PushAST(ret, arule_list);
	return ret;
}

bc_AST* bc_NewASTTypeInParameter(StringView name, bc_AST* arule_list) {
	bc_AST* ret = bc_NewAST(AST_TYPE_IN_PARAMETER_T);
	ret->Attr.StringVValue = name;
	bc_PushAST(ret, arule_list);
	return ret;
}

bc_AST* bc_NewASTTypeOutParameter(StringView name, bc_AST* arule_list) {
	bc_AST* ret = bc_NewAST(AST_TYPE_OUT_PARAMETER_T);
	ret->Attr.StringVValue = name;
	bc_PushAST(ret, arule_list);
	return ret;
}

bc_AST* bc_NewASTTypeParameterList(bc_AST* aparam, bc_AST* alist) {
	bc_AST* ret = bc_NewAST(AST_TYPE_PARAMETER_LIST_T);
	bc_PushAST(ret, alist);
	bc_PushAST(ret, aparam);
	return ret;
}

bc_AST* bc_NewASTParameterizedTypename(StringView name, bc_AST* aparams) {
	bc_AST* ret = bc_NewAST(AST_PARAMETERIZED_TYPENAME_T);
	ret->Attr.StringVValue = name;
	bc_PushAST(ret, aparams);
	return ret;
}

bc_AST* bc_NewASTTypeParameterRuleList(bc_AST* arule_list) {
	bc_AST* ret = bc_NewAST(AST_TYPE_PARAMETER_RULE_LIST_T);
	bc_PushAST(ret, arule_list);
	return ret;
}

bc_AST* bc_NewASTOperatorOverload(OperatorType type, bc_AST* aparam_list, bc_AST* abody, bc_AST* areturn) {
	bc_AST* ret = bc_NewAST(AST_OPERATOR_OVERLOAD_T);
	ret->Attr.OperatorValue = type;
	bc_PushAST(ret, aparam_list);
	bc_PushAST(ret, abody);
	bc_PushAST(ret, areturn);
	return ret;
}

bc_AST* bc_NewASTPropSet(bc_AST* aacess, bc_AST* abody) {
	bc_AST* aret = bc_NewAST(AST_PROP_SET_T);
	bc_PushAST(aret, aacess);
	bc_PushAST(aret, abody);
	return aret;
}

bc_AST* bc_NewASTPropGet(bc_AST* aacess, bc_AST* abody) {
	bc_AST* aret = bc_NewAST(AST_PROP_GET_T);
	bc_PushAST(aret, aacess);
	bc_PushAST(aret, abody);
	return aret;
}

bc_AST* bc_NewASTPropDecl(bc_AST* amodifier, bc_AST* atypename, StringView name, bc_AST* aset, bc_AST* aget) {
	bc_AST* aprop = bc_NewAST(AST_PROP_DECL_T);
	aprop->Attr.StringVValue = name;
	bc_PushAST(aprop, amodifier);
	bc_PushAST(aprop, atypename);
	bc_PushAST(aprop, aset);
	bc_PushAST(aprop, aget);
	return aprop;
}

//private
static bc_AST* ast_new_field_GetTypeName(StringView GetTypeNamev) {
	bc_AST* ret = bc_NewAST(AST_FIELD_TYPE_NAME_T);
	ret->Attr.StringVValue = GetTypeNamev;
	return ret;
}

static bc_AST* NewASTFieldAccess_name(StringView field_namev) {
	bc_AST* ret = bc_NewAST(AST_FIELD_ACCESS_NAME_T);
	ret->Attr.StringVValue = field_namev;
	return ret;
}

static bc_AST* ast_new_function_name(StringView func_namev) {
	bc_AST* ret = bc_NewAST(AST_FUNCTION_NAME_T);
	ret->Attr.StringVValue = func_namev;
	return ret;
}

static bc_AST* ast_new_method_name(StringView func_namev) {
	bc_AST* ret = bc_NewAST(AST_METHOD_NAME_T);
	ret->Attr.StringVValue = func_namev;
	return ret;
}

static bc_AST* ast_new_method_return_name(StringView return_GetTypeNamev) {
	bc_AST* ret = bc_NewAST(AST_METHOD_RETURN_NAME_T);
	ret->Attr.StringVValue = return_GetTypeNamev;
	return ret;
}

static bc_AST* NewASTParameter_GetTypeName(StringView GetTypeNamev) {
	bc_AST* ret = bc_NewAST(AST_PARAMETER_TYPE_NAME_T);
	ret->Attr.StringVValue = GetTypeNamev;
	return ret;
}

static bc_AST* NewASTParameter_access_name(StringView parameter_namev) {
	bc_AST* ret = bc_NewAST(AST_PARAMETER_ACCESS_NAME_T);
	ret->Attr.StringVValue = parameter_namev;
	return ret;
}

static bc_AST* NewASTClassDeclImpl(bc_AST* aclass_name, bc_AST* aextend_list, bc_AST* amember_list, bc_ASTTag tag) {
	bc_AST* ret = bc_NewAST(tag);
	bc_PushAST(ret, aclass_name);
	bc_PushAST(ret, aextend_list);
	bc_PushAST(ret, amember_list);
	return ret;
}