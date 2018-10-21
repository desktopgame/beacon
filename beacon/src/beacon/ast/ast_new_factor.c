#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

AST* NewASTBool(bool b) {
	return b ? NewASTTrue() : NewASTFalse();
}

AST* NewASTTrue() {
	return ast_new(AST_TRUE_T);
}

AST* NewASTFalse() {
	return ast_new(AST_FALSE_T);
}

AST* NewASTNull() {
	return ast_new(AST_NULL_T);
}

AST* NewASTAs(AST* afact, AST* atypename) {
	AST* ret = ast_new(AST_AS_T);
	PushAST(ret, afact);
	PushAST(ret, atypename);
	return ret;
}


AST* NewASTNameReference(AST* atypename) {
	AST* ret = ast_new(AST_NAME_REFERENCE_T);
	PushAST(ret, atypename);
	return ret;
}

AST* NewASTVariable(AST* a, AST* atype_args) {
	AST* ret = ast_new(AST_VARIABLE_T);
	PushAST(ret, a);
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTVariableFromString(StringView strv, AST* atype_args) {
	AST* ret = ast_new(AST_VARIABLE_T);
	ret->Attr.StringVValue = strv;
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTOpCall(AST* areceiver, AST* aargs) {
	AST* ret = ast_new(AST_OP_CALL_T);
	PushAST(ret, areceiver);
	PushAST(ret, aargs);
	return ret;
}

AST* NewASTThis() {
	return ast_new(AST_THIS_T);
}

AST* NewASTSuper() {
	return ast_new(AST_SUPER_T);
}

AST* NewASTFieldAccess(AST* afact, StringView namev, AST* atype_args) {
	AST* ret = ast_new(AST_FIELD_ACCESS_T);
	AST* aname = ast_new(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = namev;
	PushAST(ret, afact);
	PushAST(ret, aname);
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTNewInstance(AST* afqcn, AST* atype_args, AST* argument_list) {
	AST* ret = ast_new(AST_NEW_INSTANCE_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	PushAST(ret, argument_list);
	return ret;
}

AST* NewASTInstanceTof(AST* afact, AST* atype) {
	AST* ret = ast_new(AST_INSTANCEOF_T);
	PushAST(ret, afact);
	PushAST(ret, atype);
	return ret;
}

AST* NewASTExplicitBiOperator(AST* afact, operator_type type, AST* aarg) {
	AST* ret = ast_new(AST_EXPLICIT_BIOPERATOR_T);
	ret->Attr.OperatorValue = type;
	PushAST(ret, afact);
	PushAST(ret, aarg);
	return ret;
}

AST* NewASTExplicitUOperator(AST* afact, operator_type type) {
	AST* ret = ast_new(AST_EXPLICIT_UOPERATOR_T);
	ret->Attr.OperatorValue = type;
	PushAST(ret, afact);
	return ret;
}

AST* NewASTSubscriptAccess(AST* afact, AST* aindex) {
	AST* ret = ast_new(AST_SUBSCRIPT_ACCESS_T);
	PushAST(ret, afact);
	PushAST(ret, aindex);
	return ret;
}