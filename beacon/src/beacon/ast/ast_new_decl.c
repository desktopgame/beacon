#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static ast* ast_new_field_type_name(string_view type_namev);
static ast* ast_new_field_access_name(string_view field_namev);
static ast* ast_new_function_name(string_view func_namev);
static ast* ast_new_method_name(string_view func_namev);
static ast* ast_new_method_return_name(string_view return_type_namev);
static ast* ast_new_parameter_type_name(string_view type_namev);
static ast* ast_new_parameter_access_name(string_view parameter_namev);
static ast* ast_new_class_declImpl(ast* aclass_name, ast* aextend_list, ast* amember_list, ast_tag tag);

ast * ast_new_namespace_decl(ast * anamespace_path, ast * abody) {
	ast* ret = ast_new(ast_namespace_decl_T);
	ast_push(ret, anamespace_path);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_namespace_namespace_decl(ast * anamespace_path, ast * abody) {
	return ast_new_namespace_decl(anamespace_path, abody);
}

ast * ast_new_namespace_member_decl_list(ast * aforward, ast * alist) {
	ast* ret = ast_new(ast_namespace_member_decl_list_T);
	ast_push(ret, aforward);
	ast_push(ret, alist);
	return ret;
}

ast* ast_new_abstract_class_decl(ast* aclass_name, ast* aextend_list, ast* amember_list) {
	return ast_new_class_declImpl(aclass_name, aextend_list, amember_list, ast_abstract_class_decl_T);
}

ast * ast_new_class_decl(ast* aclass_name, ast* aextend_list, ast* amember_list) {
	return ast_new_class_declImpl(aclass_name, aextend_list, amember_list, ast_class_decl_T);
}

ast * ast_new_interface_decl(ast* ainterface_name, ast* asuper_interface_list, ast * amember_list) {
	ast* ret = ast_new(ast_interface_decl);
	ast_push(ret, ainterface_name);
	ast_push(ret, asuper_interface_list);
	ast_push(ret, amember_list);
	return ret;
}

ast * ast_new_enum_decl(string_view enum_namev, ast * aident_list) {
	ast* ret = ast_new(ast_enum_decl_T);
	ret->u.stringv_value = enum_namev;
	ast_push(ret, aident_list);
	return ret;
}

ast * ast_new_superclass(ast* afqcn) {
	ast* ret = ast_new(ast_class_super_T);
	ast_push(ret, afqcn);
	return ret;
}

ast * ast_new_access_member_tree(ast * amember_tree, ast * amember_list) {
	ast* ret = ast_new(ast_access_member_tree_T);
	ast_push(ret, amember_tree);
	ast_push(ret, amember_list);
	return ret;
}

ast * ast_new_access_member_list(access_level level, ast * amember_list) {
	ast* ret = ast_new(ast_access_member_list_T);
	ast* a = ast_new_access(level);
	ast_push(ret, a);
	ast_push(ret, amember_list);
	return ret;
}

ast * ast_new_access(access_level level) {
	ast* ret = ast_new(ast_access_level_T);
	ret->u.access_value = level;
	return ret;
}

ast* ast_new_modifier_list(ast* amod, ast* amod_list) {
	ast* ret = ast_new(ast_mod_Tifier_list);
	ast_push(ret, amod);
	ast_push(ret, amod_list);
	return ret;
}

ast * ast_new_modifier(modifier_type type) {
	ast* ret = ast_new(ast_mod_Tifier);
	ret->u.modifier_value = type;
	return ret;
}

ast * ast_new_member_decl(ast * amem) {
	ast* ret = ast_new(ast_member_decl_T);
	ast_push(ret, amem);
	return ret;
}

ast * ast_new_member_decl_list(ast* amember_list, ast* amember) {
	ast* ret = ast_new(ast_member_decl_list_T);
	ast_push(ret, amember_list);
	ast_push(ret, amember);
	return ret;
}

ast * ast_new_field_decl(ast* amodifier, ast* atype_name, string_view field_namev, ast* afact) {
	ast* ret = ast_new(ast_field_decl_T);
	ast_push(ret, amodifier);
	ast_push(ret, atype_name);
	ast_push(ret, ast_new_field_access_name(field_namev));
	ast_push(ret, afact);
	return ret;
}

ast * ast_new_function_decl(string_view function_namev, ast* atypeparams, ast * aparameter_list, ast * abody, ast * areturn_type) {
	ast* ret = ast_new(ast_function_decl_T);
	ast_push(ret, ast_new_function_name(function_namev));
	ast_push(ret, atypeparams);
	ast_push(ret, aparameter_list);
	ast_push(ret, abody);
	ast_push(ret, areturn_type);
	return ret;
}

ast * ast_new_function_decl_empty_params(string_view function_namev, ast* atypeparams, ast * abody, ast * areturn_type) {
	return ast_new_function_decl(function_namev, atypeparams, ast_new_blank(), abody, areturn_type);
}

ast * ast_new_method_decl(ast* amodifier, string_view func_namev, ast* atype_parameter, ast * aparameter_list, ast* abody, ast* areturn_type) {
	ast* ret = ast_new(ast_method_decl_T);
	ast_push(ret, amodifier);
	ast_push(ret, ast_new_method_name(func_namev));
	ast_push(ret, atype_parameter);
	ast_push(ret, aparameter_list);
	ast_push(ret, abody);
	ast_push(ret, areturn_type);
	return ret;
}

ast * ast_new_method_decl_empty_params(ast* amodifier, string_view func_namev, ast* atype_parameter, ast* abody, ast* areturn_type) {
	return ast_new_method_decl(amodifier, func_namev, atype_parameter, ast_new_blank(), abody, areturn_type);
}

ast * ast_new_constructor_decl(ast * aparameter_list, ast * aconstructor_chain, ast * abody) {
	ast* ret = ast_new(ast_constructor_decl_T);
	ast_push(ret, aparameter_list);
	ast_push(ret, aconstructor_chain);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_constructor_chain(constructor_chain_type chain_type, ast * aargument_list) {
	ast* ret = ast_new(ast_constructor_chain_T);
	if (chain_type == chain_type_this_T) {
		ast_push(ret, ast_new(ast_constructor_chain_this_T));
	} else {
		ast_push(ret, ast_new(ast_constructor_chain_super_T));
	}
	ast_push(ret, aargument_list);
	return ret;
}

ast * ast_new_parameter(ast* atypename, string_view parameter_access_namev) {
	ast* ret = ast_new(ast_parameter_T);
	ast_push(ret, atypename);
	ast_push(ret, ast_new_parameter_access_name(parameter_access_namev));
	return ret;
}

ast * ast_new_parameter_list(ast* atypename, string_view parameter_access_namev, ast * aparameter_list) {
	ast* ret = ast_new(ast_parameter_list_T);
	ast_push(ret, aparameter_list);
	ast_push(ret, ast_new_parameter(atypename, parameter_access_namev));
	return ret;
}

ast * ast_new_typename_list(ast * atypename, ast * atypename_list) {
	ast* ret = ast_new(ast_typename_list_T);
	ast_push(ret, atypename_list);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_typename(ast * afqcn, ast* atype_args) {
	ast* ret = ast_new(ast_typename_T);
	ast_push(ret, afqcn);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_type_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_parameter_T);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_in_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_in_parameter_T);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_out_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_out_parameter_T);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_parameter_list(ast* aparam, ast * alist) {
	ast* ret = ast_new(ast_type_parameter_list_T);
	ast_push(ret, alist);
	ast_push(ret, aparam);
	return ret;
}

ast * ast_new_parameterized_typename(string_view namev, ast * aparams) {
	ast* ret = ast_new(ast_parameter_Tized_typename);
	ret->u.stringv_value = namev;
	ast_push(ret, aparams);
	return ret;
}

ast * ast_new_type_parameter_rule_list(ast * arule_list) {
	ast* ret = ast_new(ast_type_parameter_rule_list_T);
	ast_push(ret, arule_list);
	return ret;
}

ast* ast_new_operator_overload(operator_type type, ast* aparam_list, ast* abody, ast* areturn) {
	ast* ret = ast_new(ast_operator_overload_T);
	ret->u.operator_value = type;
	ast_push(ret, aparam_list);
	ast_push(ret, abody);
	ast_push(ret, areturn);
	return ret;
}

ast* ast_new_prop_set(ast* aacess, ast* abody) {
	ast* aret = ast_new(ast_prop_set_T);
	ast_push(aret, aacess);
	ast_push(aret, abody);
	return aret;
}

ast* ast_new_prop_get(ast* aacess, ast* abody) {
	ast* aret = ast_new(ast_prop_get_T);
	ast_push(aret, aacess);
	ast_push(aret, abody);
	return aret;
}

ast* ast_new_prop_decl(ast* amodifier, ast* atypename, string_view namev, ast* aset, ast* aget) {
	ast* aprop = ast_new(ast_prop_decl_T);
	aprop->u.stringv_value = namev;
	ast_push(aprop, amodifier);
	ast_push(aprop, atypename);
	ast_push(aprop, aset);
	ast_push(aprop, aget);
	return aprop;
}

//private
static ast* ast_new_field_type_name(string_view type_namev) {
	ast* ret = ast_new(ast_field_type_name_T);
	ret->u.stringv_value = type_namev;
	return ret;
}

static ast* ast_new_field_access_name(string_view field_namev) {
	ast* ret = ast_new(ast_field_access_name_T);
	ret->u.stringv_value = field_namev;
	return ret;
}

static ast* ast_new_function_name(string_view func_namev) {
	ast* ret = ast_new(ast_function_name_T);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_name(string_view func_namev) {
	ast* ret = ast_new(ast_method_name_T);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_return_name(string_view return_type_namev) {
	ast* ret = ast_new(ast_method_return_name_T);
	ret->u.stringv_value = return_type_namev;
	return ret;
}

static ast* ast_new_parameter_type_name(string_view type_namev) {
	ast* ret = ast_new(ast_parameter_type_name_T);
	ret->u.stringv_value = type_namev;
	return ret;
}

static ast* ast_new_parameter_access_name(string_view parameter_namev) {
	ast* ret = ast_new(ast_parameter_access_name_T);
	ret->u.stringv_value = parameter_namev;
	return ret;
}

static ast* ast_new_class_declImpl(ast* aclass_name, ast* aextend_list, ast* amember_list, ast_tag tag) {
	ast* ret = ast_new(tag);
	ast_push(ret, aclass_name);
	ast_push(ret, aextend_list);
	ast_push(ret, amember_list);
	return ret;
}