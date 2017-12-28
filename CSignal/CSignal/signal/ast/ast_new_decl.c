#include "ast_new_decl.h"
#include <stdlib.h>

//proto
static ast* ast_new_field_type_name(char* type_name);
static ast* ast_new_field_access_name(char* field_name);
static ast* ast_new_function_name(char* func_name);
static ast* ast_new_function_return_name(char* return_type_name);
static ast* ast_new_parameter_type_name(char* type_name);
static ast* ast_new_parameter_access_name(char* parameter_name);

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

ast * ast_new_class_decl_unit(ast * class_decl) {
	ast* ret = ast_new(ast_class_decl_unit);
	ast_push(ret, class_decl);
	return ret;
}

ast * ast_new_class_decl(char * class_name, ast * super_class, ast * member_list) {
	ast* ret = ast_new(ast_class_decl);
	ret->u.string_value = class_name;
	ast_push(ret, super_class);
	ast_push(ret, member_list);
	return ret;
}

ast * ast_new_superclass(char * class_name) {
	ast* ret = ast_new(ast_class_super);
	ret->u.string_value = class_name;
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
	switch (level) {
		case access_public:
			return ast_new(ast_access_public);
		case access_private:
			return ast_new(ast_access_private);
		case access_protected:
			return ast_new(ast_access_protected);
	}
	return NULL;
}

ast * ast_new_modifier(modifier_type type) {
	if (type == (modifier_static | modifier_native)) {
		return ast_new(ast_modifier_static_native);
	}
	switch (type) {
//		case modifier_type_public:
//			return ast_new(ast_modifier_public);

//		case modifier_type_private:
//			return ast_new(ast_modifier_private);

//		case modifier_type_protected:
//			return ast_new(ast_modifier_protected);
		case modifier_none:
			return ast_new(ast_modifier_none);

		case modifier_static:
			return ast_new(ast_modifier_static);

		case modifier_native:
			return ast_new(ast_modifier_native);
		default:
			break;
	}
	return NULL;
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

ast * ast_new_field_decl(modifier_type modifier, char * type_name, char * field_name) {
	ast* ret = ast_new(ast_field_decl);
	ast_push(ret, ast_new_modifier(modifier));
	ast_push(ret, ast_new_field_type_name(type_name));
	ast_push(ret, ast_new_field_access_name(field_name));
	return ret;
}

ast * ast_new_function_decl(modifier_type type, char * func_name, ast * parameter_list, ast* body, char * return_type_name) {
	ast* ret = ast_new(ast_func_decl);
	ast_push(ret, ast_new_modifier(type));
	ast_push(ret, ast_new_function_name(func_name));
	ast_push(ret, parameter_list);
	ast_push(ret, body);
	ast_push(ret, ast_new_function_return_name(return_type_name));
	return ret;
}

ast * ast_new_function_decl_empty_params(modifier_type type, char * func_name, ast* body, char * return_type_name) {
	return ast_new_function_decl(type, func_name, ast_new_blank(), body, return_type_name);
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
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_parameter(char * parameter_type_name, char * parameter_access_name) {
	ast* ret = ast_new(ast_parameter);
	ast_push(ret, ast_new_parameter_type_name(parameter_type_name));
	ast_push(ret, ast_new_parameter_access_name(parameter_access_name));
	return ret;
}

ast * ast_new_parameter_list(char * parameter_type_name, char * parameter_access_name, ast * parameter_list) {
	ast* ret = ast_new(ast_parameter_list);
	ast_push(ret, ast_new_parameter(parameter_type_name, parameter_access_name));
	ast_push(ret, parameter_list);
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
	ast* ret = ast_new(ast_func_name);
	ret->u.string_value = func_name;
	return ret;
}

static ast* ast_new_function_return_name(char* return_type_name) {
	ast* ret = ast_new(ast_func_return_name);
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
