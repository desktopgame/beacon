#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

ast* NewASTBool(bool b) {
	return b ? NewASTTrue() : NewASTFalse();
}

ast * NewASTTrue() {
	return ast_new(AST_TRUE_T);
}

ast * NewASTFalse() {
	return ast_new(AST_FALSE_T);
}

ast * NewASTNull() {
	return ast_new(AST_NULL_T);
}

ast * NewASTAs(ast * afact, ast * atypename) {
	ast* ret = ast_new(AST_AS_T);
	PushAST(ret, afact);
	PushAST(ret, atypename);
	return ret;
}


ast* NewASTNameReference(ast* atypename) {
	ast* ret = ast_new(AST_NAME_REFERENCE_T);
	PushAST(ret, atypename);
	return ret;
}

ast * NewASTVariable(ast* a, ast* atype_args) {
	ast* ret = ast_new(AST_VARIABLE_T);
	PushAST(ret, a);
	PushAST(ret, atype_args);
	return ret;
}

ast * NewASTVariable_fromstr(string_view strv, ast* atype_args) {
	ast* ret = ast_new(AST_VARIABLE_T);
	ret->u.stringv_value = strv;
	PushAST(ret, atype_args);
	return ret;
}

ast* NewASTOpCall(ast* areceiver, ast* aargs) {
	ast* ret = ast_new(AST_OP_CALL_T);
	PushAST(ret, areceiver);
	PushAST(ret, aargs);
	return ret;
}

ast * NewASTThis() {
	return ast_new(AST_THIS_T);
}

ast * NewASTSuper() {
	return ast_new(AST_SUPER_T);
}

ast * NewASTFieldAccess(ast * afact, string_view namev, ast* atype_args) {
	ast* ret = ast_new(AST_FIELD_ACCESS_T);
	ast* aname = ast_new(AST_IDENTIFIER_T);
	aname->u.stringv_value = namev;
	PushAST(ret, afact);
	PushAST(ret, aname);
	PushAST(ret, atype_args);
	return ret;
}

ast * NewASTNewInstance(ast * afqcn, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(AST_NEW_INSTANCE_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	PushAST(ret, argument_list);
	return ret;
}

ast* NewASTInstanceTof(ast* afact, ast* atype) {
	ast* ret = ast_new(AST_INSTANCEOF_T);
	PushAST(ret, afact);
	PushAST(ret, atype);
	return ret;
}

ast* NewASTExplicitBiOperator(ast* afact, operator_type type, ast* aarg) {
	ast* ret = ast_new(AST_EXPLICIT_BIOPERATOR_T);
	ret->u.operator_value = type;
	PushAST(ret, afact);
	PushAST(ret, aarg);
	return ret;
}

ast* NewASTExplicitUOperator(ast* afact, operator_type type) {
	ast* ret = ast_new(AST_EXPLICIT_UOPERATOR_T);
	ret->u.operator_value = type;
	PushAST(ret, afact);
	return ret;
}

ast* NewASTSubscriptAccess(ast* afact, ast* aindex) {
	ast* ret = ast_new(AST_SUBSCRIPT_ACCESS_T);
	PushAST(ret, afact);
	PushAST(ret, aindex);
	return ret;
}