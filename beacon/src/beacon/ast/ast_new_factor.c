#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

bc_AST* NewASTBool(bool b) {
	return b ? NewASTTrue() : NewASTFalse();
}

bc_AST* NewASTTrue() {
	return bc_NewAST(AST_TRUE_T);
}

bc_AST* NewASTFalse() {
	return bc_NewAST(AST_FALSE_T);
}

bc_AST* NewASTNull() {
	return bc_NewAST(AST_NULL_T);
}

bc_AST* NewASTAs(bc_AST* afact, bc_AST* atypename) {
	bc_AST* ret = bc_NewAST(AST_AS_T);
	bc_PushAST(ret, afact);
	bc_PushAST(ret, atypename);
	return ret;
}


bc_AST* NewASTNameReference(bc_AST* atypename) {
	bc_AST* ret = bc_NewAST(AST_NAME_REFERENCE_T);
	bc_PushAST(ret, atypename);
	return ret;
}

bc_AST* NewASTVariable(bc_AST* a, bc_AST* atype_args) {
	bc_AST* ret = bc_NewAST(AST_VARIABLE_T);
	bc_PushAST(ret, a);
	bc_PushAST(ret, atype_args);
	return ret;
}

bc_AST* NewASTVariableFromString(StringView str, bc_AST* atype_args) {
	bc_AST* ret = bc_NewAST(AST_VARIABLE_T);
	ret->Attr.StringVValue = str;
	bc_PushAST(ret, atype_args);
	return ret;
}

bc_AST* NewASTOpCall(bc_AST* areceiver, bc_AST* aargs) {
	bc_AST* ret = bc_NewAST(AST_OP_CALL_T);
	bc_PushAST(ret, areceiver);
	bc_PushAST(ret, aargs);
	return ret;
}

bc_AST* NewASTThis() {
	return bc_NewAST(AST_THIS_T);
}

bc_AST* NewASTSuper() {
	return bc_NewAST(AST_SUPER_T);
}

bc_AST* NewASTFieldAccess(bc_AST* afact, StringView name, bc_AST* atype_args) {
	bc_AST* ret = bc_NewAST(AST_FIELD_ACCESS_T);
	bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	bc_PushAST(ret, afact);
	bc_PushAST(ret, aname);
	bc_PushAST(ret, atype_args);
	return ret;
}

bc_AST* NewASTNewInstance(bc_AST* afqcn, bc_AST* atype_args, bc_AST* argument_list) {
	bc_AST* ret = bc_NewAST(AST_NEW_INSTANCE_T);
	bc_PushAST(ret, afqcn);
	bc_PushAST(ret, atype_args);
	bc_PushAST(ret, argument_list);
	return ret;
}

bc_AST* NewASTInstanceTof(bc_AST* afact, bc_AST* atype) {
	bc_AST* ret = bc_NewAST(AST_INSTANCEOF_T);
	bc_PushAST(ret, afact);
	bc_PushAST(ret, atype);
	return ret;
}

bc_AST* NewASTExplicitBiOperator(bc_AST* afact, OperatorType type, bc_AST* aarg) {
	bc_AST* ret = bc_NewAST(AST_EXPLICIT_BIOPERATOR_T);
	ret->Attr.OperatorValue = type;
	bc_PushAST(ret, afact);
	bc_PushAST(ret, aarg);
	return ret;
}

bc_AST* NewASTExplicitUOperator(bc_AST* afact, OperatorType type) {
	bc_AST* ret = bc_NewAST(AST_EXPLICIT_UOPERATOR_T);
	ret->Attr.OperatorValue = type;
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTSubscriptAccess(bc_AST* afact, bc_AST* aindex) {
	bc_AST* ret = bc_NewAST(AST_SUBSCRIPT_ACCESS_T);
	bc_PushAST(ret, afact);
	bc_PushAST(ret, aindex);
	return ret;
}