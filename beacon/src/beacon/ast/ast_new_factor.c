#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

ast * ast_new_true() {
	return ast_new(ast_true);
}

ast * ast_new_false() {
	return ast_new(ast_false);
}

ast * ast_new_null() {
	return ast_new(ast_null);
}

ast * ast_new_as(ast * afact, ast * atypename) {
	ast* ret = ast_new(ast_as);
	ast_push(ret, afact);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_cast(ast * atypename, ast * afact) {
	ast* ret = ast_new(ast_cast);
	ast_push(ret, atypename);
	ast_push(ret, afact);
	return ret;
}

ast * ast_new_pre_inc(ast * a) {
	ast* ret = ast_new(ast_pre_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_pre_dec(ast * a) {
	ast* ret = ast_new(ast_pre_dec);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_inc(ast * a) {
	ast* ret = ast_new(ast_post_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_dec(ast * a) {
	ast* ret = ast_new(ast_post_dec);
	ast_push(ret, a);
	return ret;
}

ast* ast_new_name_reference(ast* atypename) {
	ast* ret = ast_new(ast_name_reference);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_variable(ast* a, ast* atype_args) {
	//assert(a->tag == ast_fqcn_class_name);
	ast* ret = ast_new(ast_variable);
	//ret->u.string_value = text_strdup(a->u.string_value);
	ast_push(ret, a);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_variable_fromstr(char * str, ast* atype_args) {
	ast* ret = ast_new(ast_variable);
	ret->u.string_value = (str);
	ast_push(ret, atype_args);
	//ast_push(ret, a);
	return ret;
}

ast* ast_new_op_call(ast* areceiver, ast* aargs) {
	ast* ret = ast_new(ast_op_call);
	ast_push(ret, areceiver);
	ast_push(ret, aargs);
	return ret;
}

ast * ast_new_this() {
	return ast_new(ast_this);
}

ast * ast_new_super() {
	return ast_new(ast_super);
}

ast * ast_new_field_access(ast * afact, char * name, ast* atype_args) {
	ast* ret = ast_new(ast_field_access);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, afact);
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_new_instance(ast * afqcn, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance);
	ast_push(ret, afqcn);
	ast_push(ret, atype_args);
	ast_push(ret, argument_list);
	return ret;
}
