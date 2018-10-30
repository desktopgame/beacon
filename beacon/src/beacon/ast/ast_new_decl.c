#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static AST* ast_new_field_GetTypeName(StringView GetTypeNamev);
static AST* NewASTFieldAccess_name(StringView field_namev);
static AST* ast_new_function_name(StringView func_namev);
static AST* ast_new_method_name(StringView func_namev);
static AST* ast_new_method_return_name(StringView return_GetTypeNamev);
static AST* NewASTParameter_GetTypeName(StringView GetTypeNamev);
static AST* NewASTParameter_access_name(StringView parameter_namev);
static AST* NewASTClassDeclImpl(AST* aclass_name, AST* aextend_list, AST* amember_list, ASTTag tag);

AST* NewASTNamespaceDecl(AST* aNamespacepath, AST* abody) {
	AST* ret = NewAST(AST_NAMESPACE_DECL_T);
	PushAST(ret, aNamespacepath);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTNamespaceNamespaceDecl(AST* aNamespacepath, AST* abody) {
	return NewASTNamespaceDecl(aNamespacepath, abody);
}

AST* NewASTNamespaceMemberDeclList(AST* aforward, AST* alist) {
	AST* ret = NewAST(AST_NAMESPACE_MEMBER_DECL_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, alist);
	return ret;
}

AST* NewASTAbstractClassDecl(AST* aclass_name, AST* aextend_list, AST* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_ABSTRACT_CLASS_DECL_T);
}

AST* NewASTClassDecl(AST* aclass_name, AST* aextend_list, AST* amember_list) {
	return NewASTClassDeclImpl(aclass_name, aextend_list, amember_list, AST_CLASS_DECL_T);
}

AST* NewASTInterfaceDecl(AST* ainterface_name, AST* asuper_interface_list, AST* amember_list) {
	AST* ret = NewAST(AST_INTERFACE_DECL);
	PushAST(ret, ainterface_name);
	PushAST(ret, asuper_interface_list);
	PushAST(ret, amember_list);
	return ret;
}

AST* NewASTEnumDecl(StringView enum_namev, AST* aident_list) {
	AST* ret = NewAST(AST_ENUM_DECL_T);
	ret->Attr.StringVValue = enum_namev;
	PushAST(ret, aident_list);
	return ret;
}

AST* NewASTSuperclass(AST* afqcn) {
	AST* ret = NewAST(AST_CLASS_SUPER_T);
	PushAST(ret, afqcn);
	return ret;
}

AST* NewASTAccessMemberTree(AST* amember_tree, AST* amember_list) {
	AST* ret = NewAST(AST_ACCESS_MEMBER_TREE_T);
	PushAST(ret, amember_tree);
	PushAST(ret, amember_list);
	return ret;
}

AST* NewASTAccessMemberList(AccessLevel level, AST* amember_list) {
	AST* ret = NewAST(AST_ACCESS_MEMBER_LIST_T);
	AST* a = NewASTAccess(level);
	PushAST(ret, a);
	PushAST(ret, amember_list);
	return ret;
}

AST* NewASTAccess(AccessLevel level) {
	AST* ret = NewAST(AST_ACCESS_LEVEL_T);
	ret->Attr.AccessValue = level;
	return ret;
}

AST* NewASTModifierList(AST* amod, AST* amod_list) {
	AST* ret = NewAST(AST_MOD_Tifier_list);
	PushAST(ret, amod);
	PushAST(ret, amod_list);
	return ret;
}

AST* NewASTModifier(ModifierType type) {
	AST* ret = NewAST(AST_MOD_Tifier);
	ret->Attr.ModifierValue = type;
	return ret;
}

AST* NewASTMemberDecl(AST* amem) {
	AST* ret = NewAST(AST_MEMBER_DECL_T);
	PushAST(ret, amem);
	return ret;
}

AST* NewASTMemberDeclList(AST* amember_list, AST* amember) {
	AST* ret = NewAST(AST_MEMBER_DECL_LIST_T);
	PushAST(ret, amember_list);
	PushAST(ret, amember);
	return ret;
}

AST* NewASTFieldDecl(AST* amodifier, AST* aGetTypeName, StringView field_namev, AST* afact) {
	AST* ret = NewAST(AST_FIELD_DECL_T);
	PushAST(ret, amodifier);
	PushAST(ret, aGetTypeName);
	PushAST(ret, NewASTFieldAccess_name(field_namev));
	PushAST(ret, afact);
	return ret;
}

AST* NewASTFunctionDecl(StringView function_namev, AST* atypeparams, AST* aparameter_list, AST* abody, AST* areturn_type) {
	AST* ret = NewAST(AST_FUNCTION_DECL_T);
	PushAST(ret, ast_new_function_name(function_namev));
	PushAST(ret, atypeparams);
	PushAST(ret, aparameter_list);
	PushAST(ret, abody);
	PushAST(ret, areturn_type);
	return ret;
}

AST* NewASTFunctionDeclEmptyParams(StringView function_namev, AST* atypeparams, AST* abody, AST* areturn_type) {
	return NewASTFunctionDecl(function_namev, atypeparams, NewASTBlank(), abody, areturn_type);
}

AST* NewASTMethodDecl(AST* amodifier, StringView func_namev, AST* atype_parameter, AST* aparameter_list, AST* abody, AST* areturn_type) {
	AST* ret = NewAST(AST_METHOD_DECL_T);
	PushAST(ret, amodifier);
	PushAST(ret, ast_new_method_name(func_namev));
	PushAST(ret, atype_parameter);
	PushAST(ret, aparameter_list);
	PushAST(ret, abody);
	PushAST(ret, areturn_type);
	return ret;
}

AST* NewASTMethodDeclEmptyParams(AST* amodifier, StringView func_namev, AST* atype_parameter, AST* abody, AST* areturn_type) {
	return NewASTMethodDecl(amodifier, func_namev, atype_parameter, NewASTBlank(), abody, areturn_type);
}

AST* NewASTConstructorDecl(AST* aparameter_list, AST* aconstructor_chain, AST* abody) {
	AST* ret = NewAST(AST_CONSTRUCTOR_DECL_T);
	PushAST(ret, aparameter_list);
	PushAST(ret, aconstructor_chain);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTConstructorChain(ConstructorChainType chain_type, AST* aargument_list) {
	AST* ret = NewAST(AST_CONSTRUCTOR_CHAIN_T);
	if (chain_type == CHAIN_TYPE_THIS_T) {
		PushAST(ret, NewAST(AST_CONSTRUCTOR_CHAIN_THIS_T));
	} else {
		PushAST(ret, NewAST(AST_CONSTRUCTOR_CHAIN_SUPER_T));
	}
	PushAST(ret, aargument_list);
	return ret;
}

AST* NewASTParameter(AST* atypename, StringView parameter_access_namev) {
	AST* ret = NewAST(AST_PARAMETER_T);
	PushAST(ret, atypename);
	PushAST(ret, NewASTParameter_access_name(parameter_access_namev));
	return ret;
}

AST* NewASTParameterList(AST* atypename, StringView parameter_access_namev, AST* aparameter_list) {
	AST* ret = NewAST(AST_PARAMETER_LIST_T);
	PushAST(ret, aparameter_list);
	PushAST(ret, NewASTParameter(atypename, parameter_access_namev));
	return ret;
}

AST* NewASTTypenameList(AST* atypename, AST* atypename_list) {
	AST* ret = NewAST(AST_TYPENAME_LIST_T);
	PushAST(ret, atypename_list);
	PushAST(ret, atypename);
	return ret;
}

AST* NewASTTypename(AST* afqcn, AST* atype_args) {
	AST* ret = NewAST(AST_TYPENAME_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTTypeParameter(StringView namev, AST* arule_list) {
	AST* ret = NewAST(AST_TYPE_PARAMETER_T);
	ret->Attr.StringVValue = namev;
	PushAST(ret, arule_list);
	return ret;
}

AST* NewASTTypeInParameter(StringView namev, AST* arule_list) {
	AST* ret = NewAST(AST_TYPE_IN_PARAMETER_T);
	ret->Attr.StringVValue = namev;
	PushAST(ret, arule_list);
	return ret;
}

AST* NewASTTypeOutParameter(StringView namev, AST* arule_list) {
	AST* ret = NewAST(AST_TYPE_OUT_PARAMETER_T);
	ret->Attr.StringVValue = namev;
	PushAST(ret, arule_list);
	return ret;
}

AST* NewASTTypeParameterList(AST* aparam, AST* alist) {
	AST* ret = NewAST(AST_TYPE_PARAMETER_LIST_T);
	PushAST(ret, alist);
	PushAST(ret, aparam);
	return ret;
}

AST* NewASTParameterizedTypename(StringView namev, AST* aparams) {
	AST* ret = NewAST(AST_PARAMETERIZED_TYPENAME_T);
	ret->Attr.StringVValue = namev;
	PushAST(ret, aparams);
	return ret;
}

AST* NewASTTypeParameterRuleList(AST* arule_list) {
	AST* ret = NewAST(AST_TYPE_PARAMETER_RULE_LIST_T);
	PushAST(ret, arule_list);
	return ret;
}

AST* NewASTOperatorOverload(OperatorType type, AST* aparam_list, AST* abody, AST* areturn) {
	AST* ret = NewAST(AST_OPERATOR_OVERLOAD_T);
	ret->Attr.OperatorValue = type;
	PushAST(ret, aparam_list);
	PushAST(ret, abody);
	PushAST(ret, areturn);
	return ret;
}

AST* NewASTPropSet(AST* aacess, AST* abody) {
	AST* aret = NewAST(AST_PROP_SET_T);
	PushAST(aret, aacess);
	PushAST(aret, abody);
	return aret;
}

AST* NewASTPropGet(AST* aacess, AST* abody) {
	AST* aret = NewAST(AST_PROP_GET_T);
	PushAST(aret, aacess);
	PushAST(aret, abody);
	return aret;
}

AST* NewASTPropDecl(AST* amodifier, AST* atypename, StringView namev, AST* aset, AST* aget) {
	AST* aprop = NewAST(AST_PROP_DECL_T);
	aprop->Attr.StringVValue = namev;
	PushAST(aprop, amodifier);
	PushAST(aprop, atypename);
	PushAST(aprop, aset);
	PushAST(aprop, aget);
	return aprop;
}

//private
static AST* ast_new_field_GetTypeName(StringView GetTypeNamev) {
	AST* ret = NewAST(AST_FIELD_TYPE_NAME_T);
	ret->Attr.StringVValue = GetTypeNamev;
	return ret;
}

static AST* NewASTFieldAccess_name(StringView field_namev) {
	AST* ret = NewAST(AST_FIELD_ACCESS_NAME_T);
	ret->Attr.StringVValue = field_namev;
	return ret;
}

static AST* ast_new_function_name(StringView func_namev) {
	AST* ret = NewAST(AST_FUNCTION_NAME_T);
	ret->Attr.StringVValue = func_namev;
	return ret;
}

static AST* ast_new_method_name(StringView func_namev) {
	AST* ret = NewAST(AST_METHOD_NAME_T);
	ret->Attr.StringVValue = func_namev;
	return ret;
}

static AST* ast_new_method_return_name(StringView return_GetTypeNamev) {
	AST* ret = NewAST(AST_METHOD_RETURN_NAME_T);
	ret->Attr.StringVValue = return_GetTypeNamev;
	return ret;
}

static AST* NewASTParameter_GetTypeName(StringView GetTypeNamev) {
	AST* ret = NewAST(AST_PARAMETER_TYPE_NAME_T);
	ret->Attr.StringVValue = GetTypeNamev;
	return ret;
}

static AST* NewASTParameter_access_name(StringView parameter_namev) {
	AST* ret = NewAST(AST_PARAMETER_ACCESS_NAME_T);
	ret->Attr.StringVValue = parameter_namev;
	return ret;
}

static AST* NewASTClassDeclImpl(AST* aclass_name, AST* aextend_list, AST* amember_list, ASTTag tag) {
	AST* ret = NewAST(tag);
	PushAST(ret, aclass_name);
	PushAST(ret, aextend_list);
	PushAST(ret, amember_list);
	return ret;
}