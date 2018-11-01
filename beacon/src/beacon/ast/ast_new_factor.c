#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

AST* NewASTBool(bool b) {
	return b ? NewASTTrue() : NewASTFalse();
}

AST* NewASTTrue() {
	return NewAST(AST_TRUE_T);
}

AST* NewASTFalse() {
	return NewAST(AST_FALSE_T);
}

AST* NewASTNull() {
	return NewAST(AST_NULL_T);
}

AST* NewASTAs(AST* afact, AST* atypename) {
	AST* ret = NewAST(AST_AS_T);
	PushAST(ret, afact);
	PushAST(ret, atypename);
	return ret;
}


AST* NewASTNameReference(AST* atypename) {
	AST* ret = NewAST(AST_NAME_REFERENCE_T);
	PushAST(ret, atypename);
	return ret;
}

AST* NewASTVariable(AST* a, AST* atype_args) {
	AST* ret = NewAST(AST_VARIABLE_T);
	PushAST(ret, a);
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTVariableFromString(StringView str, AST* atype_args) {
	AST* ret = NewAST(AST_VARIABLE_T);
	ret->Attr.StringVValue = str;
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTOpCall(AST* areceiver, AST* aargs) {
	AST* ret = NewAST(AST_OP_CALL_T);
	PushAST(ret, areceiver);
	PushAST(ret, aargs);
	return ret;
}

AST* NewASTThis() {
	return NewAST(AST_THIS_T);
}

AST* NewASTSuper() {
	return NewAST(AST_SUPER_T);
}

AST* NewASTFieldAccess(AST* afact, StringView name, AST* atype_args) {
	AST* ret = NewAST(AST_FIELD_ACCESS_T);
	AST* aname = NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	PushAST(ret, afact);
	PushAST(ret, aname);
	PushAST(ret, atype_args);
	return ret;
}

AST* NewASTNewInstance(AST* afqcn, AST* atype_args, AST* argument_list) {
	AST* ret = NewAST(AST_NEW_INSTANCE_T);
	PushAST(ret, afqcn);
	PushAST(ret, atype_args);
	PushAST(ret, argument_list);
	return ret;
}

AST* NewASTInstanceTof(AST* afact, AST* atype) {
	AST* ret = NewAST(AST_INSTANCEOF_T);
	PushAST(ret, afact);
	PushAST(ret, atype);
	return ret;
}

AST* NewASTExplicitBiOperator(AST* afact, OperatorType type, AST* aarg) {
	AST* ret = NewAST(AST_EXPLICIT_BIOPERATOR_T);
	ret->Attr.OperatorValue = type;
	PushAST(ret, afact);
	PushAST(ret, aarg);
	return ret;
}

AST* NewASTExplicitUOperator(AST* afact, OperatorType type) {
	AST* ret = NewAST(AST_EXPLICIT_UOPERATOR_T);
	ret->Attr.OperatorValue = type;
	PushAST(ret, afact);
	return ret;
}

AST* NewASTSubscriptAccess(AST* afact, AST* aindex) {
	AST* ret = NewAST(AST_SUBSCRIPT_ACCESS_T);
	PushAST(ret, afact);
	PushAST(ret, aindex);
	return ret;
}