#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static ast* ast_new_field_GetTypeName(string_view GetTypeNamev);
static ast* NewASTFieldAccess_name(string_view field_namev);
static ast* ast_new_function_name(string_view func_namev);
static ast* ast_new_method_name(string_view func_namev);
static ast* ast_new_method_return_name(string_view return_GetTypeNamev);
static ast* NewASTParameter_GetTypeName(string_view GetTypeNamev);
static ast* NewASTParameter_access_name(string_view parameter_namev);
static ast* NewASTClassDeclImpl(ast* aclass_name, ast* aextend_list, ast* amember_list, ast_tag tag);

ast * NewASTNamespaceDecl(ast * anamespace_path, ast * abody) {
	ast* ret = ast_new(AST_NAMESPACE_DECL_T);
	PushAST(ret, anamespace_path);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTNamespaceNamespaceDecl(ast * anamespace_path, ast * abody) {
	return NewASTNamespaceDecl(anamespace_path, abody);
}

ast * NewASTNamespaceMemberDeclList(ast * aforward, ast * alist) {
	ast* ret = ast_new(AST_NAMESPACE_MEMBER_DECL_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, alist);
	return ret;
}

ast* NewASTAbstractClassDecl(ast* aclass_name, ast* aextend_list, ast* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_ABSTRACT_CLASS_DECL_T);
}

ast * NewASTClassDecl(ast* aclass_name, ast* aextend_list, ast* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_CLASS_DECL_T);
}

ast * NewASTInterfaceDecl(ast* ainterface_name, ast* asuper_interface_list, ast * amember_list) {
	ast* ret = ast_new(AST_INTERFACE_DECL);
	PushAST(ret, ainterface_name);
	PushAST(ret, asuper_interface_list);
	PushAST(ret, amember_list);
	return ret;
}

ast * NewASTEnumDecl(string_view enum_namev, ast * aident_list) {
	ast* ret = ast_new(AST_ENUM_DECL_T);
	ret->u.stringv_value = enum_namev;
	PushAST(ret, aident_list);
	return ret;
}

ast * NewASTSuperclass(ast* afqcn) {
	ast* ret = ast_new(AST_CLASS_SUPER_T);
	PushAST(ret, afqcn);
	return ret;
}

ast * NewASTAccessMemberTree(ast * amember_tree, ast * amember_list) {
	ast* ret = ast_new(AST_ACCESS_MEMBER_TREE_T);
	PushAST(ret, amember_tree);
	PushAST(ret, amember_list);
	return ret;
}

ast * NewASTAccessMemberList(access_level level, ast * amember_list) {
	ast* ret = ast_new(AST_ACCESS_MEMBER_LIST_T);
	ast* a = NewASTAccess(level);
	PushAST(ret, a);
	PushAST(ret, amember_list);
	return ret;
}

ast * NewASTAccess(access_level level) {
	ast* ret = ast_new(AST_ACCESS_LEVEL_T);
	ret->u.access_value = level;
	return ret;
}

ast* NewASTModifierList(ast* amod, ast* amod_list) {
	ast* ret = ast_new(AST_MOD_Tifier_list);
	PushAST(ret, amod);
	PushAST(ret, amod_list);
	return ret;
}

ast * NewASTModifier(modifier_type type) {
	ast* ret = ast_new(AST_MOD_Tifier);
	ret->u.modifier_value = type;
	return ret;
}

ast * NewASTMemberDecl(ast * amem) {
	ast* ret = ast_new(AST_MEMBER_DECL_T);
	PushAST(ret, amem);
	return ret;
}

ast * NewASTMemberDeclList(ast* amember_list, ast* amember) {
	ast* ret = ast_new(AST_MEMBER_DECL_LIST_T);
	PushAST(ret, amember_list);
	PushAST(ret, amember);
	return ret;
}

ast * NewASTFieldDecl(ast* amodifier, ast* aGetTypeName, string_view field_namev, ast* afact) {
	ast* ret = ast_new(AST_FIELD_DECL_T);
	PushAST(ret, amodifier);
	PushAST(ret, aGetTypeName);
	PushAST(ret, NewASTFieldAccess_name(field_namev));
	PushAST(ret, afact);
	return ret;
}

ast * NewASTFunctionDecl(string_view function_namev, ast* atypeparams, ast * aparameter_list, ast * abody, ast * areturn_type) {
	ast* ret = ast_new(AST_FUNCTION_DECL_T);
	PushAST(ret, ast_new_function_name(function_namev));
	PushAST(ret, atypeparams);
	PushAST(ret, aparameter_list);
	PushAST(ret, abody);
	PushAST(ret, areturn_type);
	return ret;
}

ast * NewASTFunctionDeclEmptyParams(string_view function_namev, ast* atypeparams, ast * abody, ast * areturn_type) {
	return NewASTFunctionDecl(function_namev, atypeparams, NewASTBlank(), abody, areturn_type);
}

ast * NewASTMethodDecl(ast* amodifier, string_view func_namev, ast* atype_parameter, ast * aparameter_list, ast* abody, ast* areturn_type) {
	ast* ret = ast_new(AST_METHOD_DECL_T);
	PushAST(ret, amodifier);
	PushAST(ret, ast_new_method_name(func_namev));
	PushAST(ret, atype_parameter);
	PushAST(ret, aparameter_list);
	PushAST(ret, abody);
	PushAST(ret, areturn_type);
	return ret;
}

ast * NewASTMethodDeclEmptyParams(ast* amodifier, string_view func_namev, ast* atype_parameter, ast* abody, ast* areturn_type) {
	return NewASTMethodDecl(amodifier, func_namev, atype_parameter, NewASTBlank(), abody, areturn_type);
}

ast * NewASTConstructorDecl(ast * aparameter_list, ast * aconstructor_chain, ast * abody) {
	ast* ret = ast_new(AST_CONSTRUCTOR_DECL_T);
	PushAST(ret, aparameter_list);
	PushAST(ret, aconstructor_chain);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTConstructorChain(constructor_chain_type chain_type, ast * aargument_list) {
	ast* ret = ast_new(AST_CONSTRUCTOR_CHAIN_T);
	if (chain_type == CHAIN_TYPE_THIS_T) {
		PushAST(ret, ast_new(AST_CONSTRUCTOR_CHAIN_THIS_T));
	} else {
		PushAST(ret, ast_new(AST_CONSTRUCTOR_CHAIN_SUPER_T));
	}
	PushAST(ret, aargument_list);
	return ret;
}

ast * NewASTParameter(ast* atypename, string_view parameter_access_namev) {
	ast* ret = ast_new(AST_PARAMETER_T);
	PushAST(ret, atypename);
	PushAST(ret, NewASTParameter_access_name(parameter_access_namev));
	return ret;
}

ast * NewASTParameterList(ast* atypename, string_view parameter_access_namev, ast * aparameter_list) {
	ast* ret = ast_new(AST_PARAMETER_LIST_T);
	PushAST(ret, aparameter_list);
	PushAST(ret, NewASTParameter(atypename, parameter_access_namev));
	return ret;
}

ast * NewASTTypenameList(ast * atypename, ast * atypename_list) {
	ast* ret = ast_new(AST_TYPENAME_LIST_T);
	PushAST(ret, atypename_list);
	PushAST(ret, atypename);
	return ret;
}

ast * NewASTTypename(ast * afqcn, ast* atype_args) {
	ast* ret = ast_new(AST_TYPENAME_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	return ret;
}

ast * NewASTTypeParameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(AST_TYPE_PARAMETER_T);
	ret->u.stringv_value = namev;
	PushAST(ret, arule_list);
	return ret;
}

ast * NewASTTypeInParameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(AST_TYPE_IN_PARAMETER_T);
	ret->u.stringv_value = namev;
	PushAST(ret, arule_list);
	return ret;
}

ast * NewASTTypeOutParameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(AST_TYPE_OUT_PARAMETER_T);
	ret->u.stringv_value = namev;
	PushAST(ret, arule_list);
	return ret;
}

ast * NewASTTypeParameterList(ast* aparam, ast * alist) {
	ast* ret = ast_new(AST_TYPE_PARAMETER_LIST_T);
	PushAST(ret, alist);
	PushAST(ret, aparam);
	return ret;
}

ast * NewASTParameterizedTypename(string_view namev, ast * aparams) {
	ast* ret = ast_new(AST_PARAMETERIZED_TYPENAME_T);
	ret->u.stringv_value = namev;
	PushAST(ret, aparams);
	return ret;
}

ast * NewASTTypeParameterRuleList(ast * arule_list) {
	ast* ret = ast_new(AST_TYPE_PARAMETER_RULE_LIST_T);
	PushAST(ret, arule_list);
	return ret;
}

ast* NewASTOperatorOverload(operator_type type, ast* aparam_list, ast* abody, ast* areturn) {
	ast* ret = ast_new(AST_OPERATOR_OVERLOAD_T);
	ret->u.operator_value = type;
	PushAST(ret, aparam_list);
	PushAST(ret, abody);
	PushAST(ret, areturn);
	return ret;
}

ast* NewASTPropSet(ast* aacess, ast* abody) {
	ast* aret = ast_new(AST_PROP_SET_T);
	PushAST(aret, aacess);
	PushAST(aret, abody);
	return aret;
}

ast* NewASTPropGet(ast* aacess, ast* abody) {
	ast* aret = ast_new(AST_PROP_GET_T);
	PushAST(aret, aacess);
	PushAST(aret, abody);
	return aret;
}

ast* NewASTPropDecl(ast* amodifier, ast* atypename, string_view namev, ast* aset, ast* aget) {
	ast* aprop = ast_new(AST_PROP_DECL_T);
	aprop->u.stringv_value = namev;
	PushAST(aprop, amodifier);
	PushAST(aprop, atypename);
	PushAST(aprop, aset);
	PushAST(aprop, aget);
	return aprop;
}

//private
static ast* ast_new_field_GetTypeName(string_view GetTypeNamev) {
	ast* ret = ast_new(AST_FIELD_TYPE_NAME_T);
	ret->u.stringv_value = GetTypeNamev;
	return ret;
}

static ast* NewASTFieldAccess_name(string_view field_namev) {
	ast* ret = ast_new(AST_FIELD_ACCESS_NAME_T);
	ret->u.stringv_value = field_namev;
	return ret;
}

static ast* ast_new_function_name(string_view func_namev) {
	ast* ret = ast_new(AST_FUNCTION_NAME_T);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_name(string_view func_namev) {
	ast* ret = ast_new(AST_METHOD_NAME_T);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_return_name(string_view return_GetTypeNamev) {
	ast* ret = ast_new(AST_METHOD_RETURN_NAME_T);
	ret->u.stringv_value = return_GetTypeNamev;
	return ret;
}

static ast* NewASTParameter_GetTypeName(string_view GetTypeNamev) {
	ast* ret = ast_new(AST_PARAMETER_TYPE_NAME_T);
	ret->u.stringv_value = GetTypeNamev;
	return ret;
}

static ast* NewASTParameter_access_name(string_view parameter_namev) {
	ast* ret = ast_new(AST_PARAMETER_ACCESS_NAME_T);
	ret->u.stringv_value = parameter_namev;
	return ret;
}

static ast* NewASTClassDeclImpl(ast* aclass_name, ast* aextend_list, ast* amember_list, ast_tag tag) {
	ast* ret = ast_new(tag);
	PushAST(ret, aclass_name);
	PushAST(ret, aextend_list);
	PushAST(ret, amember_list);
	return ret;
}