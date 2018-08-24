#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

ast * ast_new_true() {
	return ast_new(ast_true_T);
}

ast * ast_new_false() {
	return ast_new(ast_false_T);
}

ast * ast_new_null() {
	return ast_new(ast_null_T);
}

ast * ast_new_as(ast * afact, ast * atypename) {
	ast* ret = ast_new(ast_as_T);
	ast_push(ret, afact);
	ast_push(ret, atypename);
	return ret;
}


ast* ast_new_name_reference(ast* atypename) {
	ast* ret = ast_new(ast_name_reference_T);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_variable(ast* a, ast* atype_args) {
	ast* ret = ast_new(ast_variable_T);
	ast_push(ret, a);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_variable_fromstr(string_view strv, ast* atype_args) {
	ast* ret = ast_new(ast_variable_T);
	ret->u.stringv_value = strv;
	ast_push(ret, atype_args);
	return ret;
}

ast* ast_new_op_call(ast* areceiver, ast* aargs) {
	ast* ret = ast_new(ast_op_call_T);
	ast_push(ret, areceiver);
	ast_push(ret, aargs);
	return ret;
}

ast * ast_new_this() {
	return ast_new(ast_this_T);
}

ast * ast_new_super() {
	return ast_new(ast_super_T);
}

ast * ast_new_field_access(ast * afact, string_view namev, ast* atype_args) {
	ast* ret = ast_new(ast_field_access_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	ast_push(ret, afact);
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_new_instance(ast * afqcn, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance_T);
	ast_push(ret, afqcn);
	ast_push(ret, atype_args);
	ast_push(ret, argument_list);
	return ret;
}

ast* ast_new_instance_Tof(ast* afact, ast* atype) {
	ast* ret = ast_new(ast_instanceof_T);
	ast_push(ret, afact);
	ast_push(ret, atype);
	return ret;
}

ast* ast_new_explicit_bioperator(ast* afact, operator_type type, ast* aarg) {
	ast* ret = ast_new(ast_explicit_bioperator_T);
	ret->u.operator_value = type;
	ast_push(ret, afact);
	ast_push(ret, aarg);
	return ret;
}

ast* ast_new_explicit_uoperator(ast* afact, operator_type type) {
	ast* ret = ast_new(ast_explicit_uoperator_T);
	ret->u.operator_value = type;
	ast_push(ret, afact);
	return ret;
}

ast* ast_new_subscript_access(ast* afact, ast* aindex) {
	ast* ret = ast_new(ast_subscript_access);
	ast_push(ret, afact);
	ast_push(ret, aindex);
	return ret;
}