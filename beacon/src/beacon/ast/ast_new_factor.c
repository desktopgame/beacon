#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

ast* NewASTBool(bool b) {
	return b ? NewASTTrue() : NewASTFalse();
}

ast * NewASTTrue() {
	return ast_new(ast_true_T);
}

ast * NewASTFalse() {
	return ast_new(ast_false_T);
}

ast * NewASTNull() {
	return ast_new(ast_null_T);
}

ast * NewASTAs(ast * afact, ast * atypename) {
	ast* ret = ast_new(ast_as_T);
	PushAST(ret, afact);
	PushAST(ret, atypename);
	return ret;
}


ast* NewASTNameReference(ast* atypename) {
	ast* ret = ast_new(ast_name_reference_T);
	PushAST(ret, atypename);
	return ret;
}

ast * NewASTVariable(ast* a, ast* atype_args) {
	ast* ret = ast_new(ast_variable_T);
	PushAST(ret, a);
	PushAST(ret, atype_args);
	return ret;
}

ast * NewASTVariable_fromstr(string_view strv, ast* atype_args) {
	ast* ret = ast_new(ast_variable_T);
	ret->u.stringv_value = strv;
	PushAST(ret, atype_args);
	return ret;
}

ast* NewASTOpCall(ast* areceiver, ast* aargs) {
	ast* ret = ast_new(ast_op_call_T);
	PushAST(ret, areceiver);
	PushAST(ret, aargs);
	return ret;
}

ast * NewASTThis() {
	return ast_new(ast_this_T);
}

ast * NewASTSuper() {
	return ast_new(ast_super_T);
}

ast * NewASTFieldAccess(ast * afact, string_view namev, ast* atype_args) {
	ast* ret = ast_new(ast_field_access_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	PushAST(ret, afact);
	PushAST(ret, aname);
	PushAST(ret, atype_args);
	return ret;
}

ast * NewASTNewInstance(ast * afqcn, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	PushAST(ret, argument_list);
	return ret;
}

ast* NewASTInstanceTof(ast* afact, ast* atype) {
	ast* ret = ast_new(ast_instanceof_T);
	PushAST(ret, afact);
	PushAST(ret, atype);
	return ret;
}

ast* NewASTExplicitBiOperator(ast* afact, operator_type type, ast* aarg) {
	ast* ret = ast_new(ast_explicit_bioperator_T);
	ret->u.operator_value = type;
	PushAST(ret, afact);
	PushAST(ret, aarg);
	return ret;
}

ast* NewASTExplicitUOperator(ast* afact, operator_type type) {
	ast* ret = ast_new(ast_explicit_uoperator_T);
	ret->u.operator_value = type;
	PushAST(ret, afact);
	return ret;
}

ast* NewASTSubscriptAccess(ast* afact, ast* aindex) {
	ast* ret = ast_new(ast_subscript_access_T);
	PushAST(ret, afact);
	PushAST(ret, aindex);
	return ret;
}