#include "ast_new_factor.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/text.h"
#include "ast.h"

bc_AST* bc_NewASTBool(bool b) { return b ? bc_NewASTTrue() : bc_NewASTFalse(); }

bc_AST* bc_NewASTTrue() { return bc_NewAST(AST_TRUE_T); }

bc_AST* bc_NewASTFalse() { return bc_NewAST(AST_FALSE_T); }

bc_AST* bc_NewASTNull() { return bc_NewAST(AST_NULL_T); }

bc_AST* bc_NewASTAs(bc_AST* afact, bc_AST* atypename) {
        bc_AST* ret = bc_NewAST(AST_AS_T);
        bc_PushAST(ret, afact);
        bc_PushAST(ret, atypename);
        return ret;
}

bc_AST* bc_NewASTNameReference(bc_AST* atypename) {
        bc_AST* ret = bc_NewAST(AST_NAME_REFERENCE_T);
        bc_PushAST(ret, atypename);
        return ret;
}

bc_AST* bc_NewASTVariable(bc_AST* a, bc_AST* atype_args) {
        bc_AST* ret = bc_NewAST(AST_VARIABLE_T);
        bc_PushAST(ret, a);
        bc_PushAST(ret, atype_args);
        return ret;
}

bc_AST* bc_NewASTVariableFromString(bc_StringView str, bc_AST* atype_args) {
        bc_AST* ret = bc_NewAST(AST_VARIABLE_T);
        ret->Attr.StringVValue = str;
        bc_PushAST(ret, atype_args);
        return ret;
}

bc_AST* bc_NewASTOpCall(bc_AST* areceiver, bc_AST* aargs) {
        bc_AST* ret = bc_NewAST(AST_OP_CALL_T);
        bc_PushAST(ret, areceiver);
        bc_PushAST(ret, aargs);
        return ret;
}

bc_AST* bc_NewASTThis() { return bc_NewAST(AST_THIS_T); }

bc_AST* bc_NewASTSuper() { return bc_NewAST(AST_SUPER_T); }

bc_AST* bc_NewASTFieldAccess(bc_AST* afact, bc_StringView name,
                             bc_AST* atype_args) {
        bc_AST* ret = bc_NewAST(AST_FIELD_ACCESS_T);
        bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
        aname->Attr.StringVValue = name;
        bc_PushAST(ret, afact);
        bc_PushAST(ret, aname);
        bc_PushAST(ret, atype_args);
        return ret;
}

bc_AST* bc_NewASTNewInstance(bc_AST* afqcn, bc_AST* atype_args,
                             bc_AST* argument_list) {
        bc_AST* ret = bc_NewAST(AST_NEW_INSTANCE_T);
        bc_PushAST(ret, afqcn);
        bc_PushAST(ret, atype_args);
        bc_PushAST(ret, argument_list);
        return ret;
}

bc_AST* bc_NewASTInstanceTof(bc_AST* afact, bc_AST* atype) {
        bc_AST* ret = bc_NewAST(AST_INSTANCEOF_T);
        bc_PushAST(ret, afact);
        bc_PushAST(ret, atype);
        return ret;
}

bc_AST* bc_NewASTExplicitBiOperator(bc_AST* afact, bc_OperatorType type,
                                    bc_AST* aarg) {
        bc_AST* ret = bc_NewAST(AST_EXPLICIT_BIOPERATOR_T);
        ret->Attr.OperatorValue = type;
        bc_PushAST(ret, afact);
        bc_PushAST(ret, aarg);
        return ret;
}

bc_AST* bc_NewASTExplicitUOperator(bc_AST* afact, bc_OperatorType type) {
        bc_AST* ret = bc_NewAST(AST_EXPLICIT_UOPERATOR_T);
        ret->Attr.OperatorValue = type;
        bc_PushAST(ret, afact);
        return ret;
}

bc_AST* bc_NewASTSubscriptAccess(bc_AST* afact, bc_AST* aindex) {
        bc_AST* ret = bc_NewAST(AST_SUBSCRIPT_ACCESS_T);
        bc_PushAST(ret, afact);
        bc_PushAST(ret, aindex);
        return ret;
}