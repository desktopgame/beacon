#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static ast* ast_new_field_type_name(char* type_name);
static ast* ast_new_field_access_name(char* field_name);
static ast* ast_new_function_name(char* func_name);
static ast* ast_new_method_name(char* func_name);
static ast* ast_new_method_return_name(char* return_type_name);
static ast* ast_new_parameter_type_name(char* type_name);
static ast* ast_new_parameter_access_name(char* parameter_name);
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
	//ret->u.string_value = interface_name;
	ast_push(ret, ainterface_name);
	ast_push(ret, super_interface_list);
	ast_push(ret, member_list);
	return ret;
}

ast * ast_new_enum_decl(char * enum_name, ast * ident_list) {
	ast* ret = ast_new(ast_enum_decl);
	ret->u.string_value = enum_name;
	ast_push(ret, ident_list);
	return ret;
}

ast * ast_new_superclass(ast* fqcn) {
	ast* ret = ast_new(ast_class_super);
	ast_push(ret, fqcn);
//	ret->u.string_value = class_name;
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
	/*
	ast* ret = ast_new(ast_member_decl_list);
	ast_push(ret, mem);
	ast_push(ret, member_list);
	return ret;
	*/
	ast* ret = ast_new(ast_member_decl_list);
	ast_push(ret, member_list);
	ast_push(ret, member);
	return ret;
}

ast * ast_new_field_decl(ast* amodifier, ast* type_name, char * field_name) {
	ast* ret = ast_new(ast_field_decl);
	ast_push(ret, amodifier);
//	ast_push(ret, ast_new_field_type_name(type_name));
	ast_push(ret, type_name);
	ast_push(ret, ast_new_field_access_name(field_name));
	return ret;
}

ast * ast_new_function_decl(char * function_name, ast * parameter_list, ast * body, ast * return_type) {
	ast* ret = ast_new(ast_function_decl);
//	ast_push(ret, ast_new_modifier(type));
	ast_push(ret, ast_new_function_name(function_name));
	ast_push(ret, parameter_list);
	ast_push(ret, body);
	ast_push(ret, return_type);
	//ast_push(ret, ast_new_function_return_name(return_type_name));
	return ret;
}

ast * ast_new_function_decl_empty_params(char * function_name, ast * body, ast * return_type) {
	return ast_new_function_decl(function_name, ast_new_blank(), body, return_type);
}

ast * ast_new_method_decl(ast* amodifier, char * func_name, ast* atype_parameter, ast * parameter_list, ast* body, ast* return_type) {
	ast* ret = ast_new(ast_method_decl);
	ast_push(ret, amodifier);
	ast_push(ret, ast_new_method_name(func_name));
	ast_push(ret, atype_parameter);
	ast_push(ret, parameter_list);
	ast_push(ret, body);
	ast_push(ret, return_type);
	//ast_push(ret, ast_new_function_return_name(return_type_name));
	return ret;
}

ast * ast_new_method_decl_empty_params(ast* amodifier, char * func_name, ast* atype_parameter, ast* body, ast* return_type) {
	return ast_new_method_decl(amodifier, func_name, atype_parameter, ast_new_blank(), body, return_type);
}

ast * ast_new_constructor_decl(ast * parameter_list, ast * constructor_chain, ast * body) {
	ast* ret = ast_new(ast_constructor_decl);
//	ast_push(ret, ast_new_modifier(modifier));
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

ast * ast_new_parameter(ast* atypename, char * parameter_access_name) {
	ast* ret = ast_new(ast_parameter);
//	ast_push(ret, ast_new_parameter_type_name(parameter_type_name));
	ast_push(ret, atypename);
	ast_push(ret, ast_new_parameter_access_name(parameter_access_name));
	return ret;
}

ast * ast_new_parameter_list(ast* atypename, char * parameter_access_name, ast * parameter_list) {
	ast* ret = ast_new(ast_parameter_list);
//	ast_push(ret, atypename);
//	ast_push(ret, ast_new_parameter(parameter_type_name, parameter_access_name));
	ast_push(ret, parameter_list);
	ast_push(ret, ast_new_parameter(atypename, parameter_access_name));
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

ast * ast_new_type_parameter(char * name, ast* arule_list) {
	ast* ret = ast_new(ast_type_parameter);
	ret->u.string_value = name;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_in_parameter(char * name, ast* arule_list) {
	ast* ret = ast_new(ast_type_in_parameter);
	ret->u.string_value = name;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_out_parameter(char * name, ast* arule_list) {
	ast* ret = ast_new(ast_type_out_parameter);
	ret->u.string_value = name;
	ast_push(ret, arule_list);
	return ret;
}

ast * ast_new_type_parameter_list(ast* aparam, ast * alist) {
	ast* ret = ast_new(ast_type_parameter_list);
	ast_push(ret, alist);
	ast_push(ret, aparam);
	return ret;
}

ast * ast_new_parameterized_typename(char * name, ast * aparams) {
	ast* ret = ast_new(ast_parameterized_typename);
	ret->u.string_value = name;
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
static ast* ast_new_field_type_name(char* type_name) {
	ast* ret = ast_new(ast_field_type_name);
	ret->u.string_value = type_name;
	return ret;
}

static ast* ast_new_field_access_name(char* field_name) {
	ast* ret = ast_new(ast_field_access_name);
	ret->u.string_value = field_name;
	return ret;
}

static ast* ast_new_function_name(char* func_name) {
	ast* ret = ast_new(ast_function_name);
	ret->u.string_value = func_name;
	return ret;
}

static ast* ast_new_method_name(char* func_name) {
	ast* ret = ast_new(ast_method_name);
	ret->u.string_value = func_name;
	return ret;
}

static ast* ast_new_method_return_name(char* return_type_name) {
	ast* ret = ast_new(ast_method_return_name);
	ret->u.string_value = return_type_name;
	return ret;
}

static ast* ast_new_parameter_type_name(char* type_name) {
	ast* ret = ast_new(ast_parameter_type_name);
	ret->u.string_value = type_name;
	return ret;
}

static ast* ast_new_parameter_access_name(char* parameter_name) {
	ast* ret = ast_new(ast_parameter_access_name);
	ret->u.string_value = parameter_name;
	return ret;
}

static ast* ast_new_class_declImpl(ast* aclass_name, ast* extend_list, ast* member_list, ast_tag tag) {
	ast* ret = ast_new(tag);
//	ret->u.string_value = class_name;
//	ast_push(ret, super_class);
//	ast_push(ret, impl_list);
	ast_push(ret, aclass_name);
	ast_push(ret, extend_list);
	ast_push(ret, member_list);
	return ret;
}