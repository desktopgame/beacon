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
static ast* ast_new_class_declImpl(ast* aclass_name, ast* extend_list, ast* member_list, ast_tag tag);

ast * ast_new_namespace_decl(ast * namespace_path, ast * body) {
	ast* ret = ast_new(ast_namespace_decl);
	ast_push(ret, namespace_path);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_namespace_namespace_decl(ast * namespace_path, ast * body) {
	return ast_new_namespace_decl(namespace_path, body);
}

ast * ast_new_namespace_member_decl_list(ast * forward, ast * list) {
	ast* ret = ast_new(ast_namespace_member_decl_list);
	ast_push(ret, forward);
	ast_push(ret, list);
	return ret;
}

ast* ast_new_abstract_class_decl(ast* aclass_name, ast* extend_list, ast* member_list) {
	return ast_new_class_declImpl(aclass_name, extend_list, member_list, ast_abstract_class_decl);
}

ast * ast_new_class_decl(ast* aclass_name, ast* extend_list, ast* member_list) {
	return ast_new_class_declImpl(aclass_name, extend_list, member_list, ast_class_decl);
}

ast * ast_new_interface_decl(ast* ainterface_name, ast* super_interface_list, ast * member_list) {
	ast* ret = ast_new(ast_interface_decl);
	ast_push(ret, ainterface_name);
	ast_push(ret, super_interface_list);
	ast_push(ret, member_list);
	return ret;
}

ast * ast_new_enum_decl(string_view enum_namev, ast * ident_list) {
	ast* ret = ast_new(ast_enum_decl);
	ret->u.stringv_value = enum_namev;
	ast_push(ret, ident_list);
	return ret;
}

ast * ast_new_superclass(ast* fqcn) {
	ast* ret = ast_new(ast_class_super);
	ast_push(ret, fqcn);
	return ret;
}

ast * ast_new_access_member_tree(ast * member_tree, ast * member_list) {
	ast* ret = ast_new(ast_access_member_tree);
	ast_push(ret, member_tree);
	ast_push(ret, member_list);
	return ret;
}

ast * ast_new_access_member_list(access_level level, ast * member_list) {
	ast* ret = ast_new(ast_access_member_list);
	ast* a = ast_new_access(level);
	ast_push(ret, a);
	ast_push(ret, member_list);
	return ret;
}

ast * ast_new_access(access_level level) {
	ast* ret = ast_new(ast_access_level);
	ret->u.access_value = level;
	return ret;
}

ast* ast_new_modifier_list(ast* amod, ast* amod_list) {
	ast* ret = ast_new(ast_modifier_list);
	ast_push(ret, amod);
	ast_push(ret, amod_list);
	return ret;
}

ast * ast_new_modifier(modifier_type type) {
	ast* ret = ast_new(ast_modifier);
	ret->u.modifier_value = type;
	return ret;
}

ast * ast_new_member_decl(ast * mem) {
	ast* ret = ast_new(ast_member_decl);
	ast_push(ret, mem);
	return ret;
}

ast * ast_new_member_decl_list(ast* member_list, ast* member) {
	ast* ret = ast_new(ast_member_decl_list);
	ast_push(ret, member_list);
	ast_push(ret, member);
	return ret;
}

ast * ast_new_field_decl(ast* amodifier, ast* type_name, string_view field_namev) {
	ast* ret = ast_new(ast_field_decl);
	ast_push(ret, amodifier);
	ast_push(ret, type_name);
	ast_push(ret, ast_new_field_access_name(field_namev));
	return ret;
}

ast * ast_new_function_decl(string_view function_namev, ast * parameter_list, ast * body, ast * return_type) {
	ast* ret = ast_new(ast_function_decl);
	ast_push(ret, ast_new_function_name(function_namev));
	ast_push(ret, parameter_list);
	ast_push(ret, body);
	ast_push(ret, return_type);
	return ret;
}

ast * ast_new_function_decl_empty_params(string_view function_namev, ast * body, ast * return_type) {
	return ast_new_function_decl(function_namev, ast_new_blank(), body, return_type);
}

ast * ast_new_method_decl(ast* amodifier, string_view func_namev, ast* atype_parameter, ast * parameter_list, ast* body, ast* return_type) {
	ast* ret = ast_new(ast_method_decl);
	ast_push(ret, amodifier);
	ast_push(ret, ast_new_method_name(func_namev));
	ast_push(ret, atype_parameter);
	ast_push(ret, parameter_list);
	ast_push(ret, body);
	ast_push(ret, return_type);
	return ret;
}

ast * ast_new_method_decl_empty_params(ast* amodifier, string_view func_namev, ast* atype_parameter, ast* body, ast* return_type) {
	return ast_new_method_decl(amodifier, func_namev, atype_parameter, ast_new_blank(), body, return_type);
}

ast * ast_new_constructor_decl(ast * parameter_list, ast * constructor_chain, ast * body) {
	ast* ret = ast_new(ast_constructor_decl);
	ast_push(ret, parameter_list);
	ast_push(ret, constructor_chain);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_constructor_chain(constructor_chain_type chain_type, ast * argument_list) {
	ast* ret = ast_new(ast_constructor_chain);
	if (chain_type == chain_type_this) {
		ast_push(ret, ast_new(ast_constructor_chain_this));
	} else {
		ast_push(ret, ast_new(ast_constructor_chain_super));
	}
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_parameter(ast* atypename, string_view parameter_access_namev) {
	ast* ret = ast_new(ast_parameter);
	ast_push(ret, atypename);
	ast_push(ret, ast_new_parameter_access_name(parameter_access_namev));
	return ret;
}

ast * ast_new_parameter_list(ast* atypename, string_view parameter_access_namev, ast * parameter_list) {
	ast* ret = ast_new(ast_parameter_list);
	ast_push(ret, parameter_list);
	ast_push(ret, ast_new_parameter(atypename, parameter_access_namev));
	return ret;
}

ast * ast_new_typename_list(ast * atypename, ast * typename_list) {
	ast* ret = ast_new(ast_typename_list);
	ast_push(ret, typename_list);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_typename(ast * fqcn, ast* atype_args) {
	ast* ret = ast_new(ast_typename);
	ast_push(ret, fqcn);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_type_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_parameter);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_in_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_in_parameter);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_out_parameter(string_view namev, ast* arule_list) {
	ast* ret = ast_new(ast_type_out_parameter);
	ret->u.stringv_value = namev;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_parameter_list(ast* aparam, ast * alist) {
	ast* ret = ast_new(ast_type_parameter_list);
	ast_push(ret, alist);
	ast_push(ret, aparam);
	return ret;
}

ast * ast_new_parameterized_typename(string_view namev, ast * aparams) {
	ast* ret = ast_new(ast_parameterized_typename);
	ret->u.stringv_value = namev;
	ast_push(ret, aparams);
	return ret;
}

ast * ast_new_type_parameter_rule_list(ast * arule_list) {
	ast* ret = ast_new(ast_type_parameter_rule_list);
	ast_push(ret, arule_list);
	return ret;
}

ast* ast_new_operator_overload(operator_type type, ast* aparam_list, ast* abody, ast* areturn) {
	ast* ret = ast_new(ast_operator_overload);
	ret->u.operator_value = type;
	ast_push(ret, aparam_list);
	ast_push(ret, abody);
	ast_push(ret, areturn);
	return ret;
}

//private
static ast* ast_new_field_type_name(string_view type_namev) {
	ast* ret = ast_new(ast_field_type_name);
	ret->u.stringv_value = type_namev;
	return ret;
}

static ast* ast_new_field_access_name(string_view field_namev) {
	ast* ret = ast_new(ast_field_access_name);
	ret->u.stringv_value = field_namev;
	return ret;
}

static ast* ast_new_function_name(string_view func_namev) {
	ast* ret = ast_new(ast_function_name);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_name(string_view func_namev) {
	ast* ret = ast_new(ast_method_name);
	ret->u.stringv_value = func_namev;
	return ret;
}

static ast* ast_new_method_return_name(string_view return_type_namev) {
	ast* ret = ast_new(ast_method_return_name);
	ret->u.stringv_value = return_type_namev;
	return ret;
}

static ast* ast_new_parameter_type_name(string_view type_namev) {
	ast* ret = ast_new(ast_parameter_type_name);
	ret->u.stringv_value = type_namev;
	return ret;
}

static ast* ast_new_parameter_access_name(string_view parameter_namev) {
	ast* ret = ast_new(ast_parameter_access_name);
	ret->u.stringv_value = parameter_namev;
	return ret;
}

static ast* ast_new_class_declImpl(ast* aclass_name, ast* extend_list, ast* member_list, ast_tag tag) {
	ast* ret = ast_new(tag);
	ast_push(ret, aclass_name);
	ast_push(ret, extend_list);
	ast_push(ret, member_list);
	return ret;
}