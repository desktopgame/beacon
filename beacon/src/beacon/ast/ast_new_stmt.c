#include "ast_new_stmt.h"

bc_AST* MallocASTStmt(bc_AST* astmt, const char* filename, int lineno) {
	bc_AST* ret = bc_MallocAST(AST_STMT_T, filename, lineno);
	bc_PushAST(ret, astmt);
	return ret;
}

bc_AST* NewASTStmtList(bc_AST* astmt, bc_AST* astmt_list) {
	bc_AST* ret = bc_NewAST(AST_STMT_LIST_T);
	bc_PushAST(ret, astmt);
	bc_PushAST(ret, astmt_list);
	return ret;
}

bc_AST* NewASTIf(bc_AST* acond, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_IF_T);
	bc_PushAST(ret, acond);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* NewASTElse(bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_ELSE_T);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* NewASTIfElse(bc_AST* acond, bc_AST* atrueBody, bc_AST* afalseBody) {
	bc_AST* ret = bc_NewAST(AST_IF_ELSE_T);
	bc_PushAST(ret, NewASTIf(acond, atrueBody));
	bc_PushAST(ret, NewASTElse(afalseBody));
	return ret;
}

bc_AST* NewASTIfElifList(bc_AST* acond, bc_AST* atrueBody, bc_AST* aelifList) {
	bc_AST* ret = bc_NewAST(AST_IF_ELIF_LIST_T);
	bc_PushAST(ret, NewASTIf(acond, atrueBody));
	bc_PushAST(ret, aelifList);
	return ret;
}

bc_AST* NewASTIfElifListElse(bc_AST* acond, bc_AST* atrueBody, bc_AST* aelifList, bc_AST* aelseBody) {
	bc_AST* ret = bc_NewAST(AST_IF_ELIF_LIST_ELSE_T);
	bc_PushAST(ret, NewASTIfElifList(acond, atrueBody, aelifList));
	bc_PushAST(ret, NewASTElse(aelseBody));
	return ret;
}

bc_AST* NewASTElifList(bc_AST* aforward, bc_AST* atail) {
	bc_AST* ret = bc_NewAST(AST_ELIF_LIST_T);
	bc_PushAST(ret, aforward);
	bc_PushAST(ret, atail);
	return ret;
}

bc_AST* NewASTElif(bc_AST* acond, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_ELIF_T);
	bc_PushAST(ret, acond);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* NewASTWhile(bc_AST* acond, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_WHILE_T);
	bc_PushAST(ret, acond);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* NewASTBreak() {
	return bc_NewAST(AST_BREAK_T);
}

bc_AST* NewASTContinue() {
	return bc_NewAST(AST_CONTINUE_T);
}

bc_AST* NewASTReturn(bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_RETURN_T);
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTReturnEmpty() {
	return bc_NewAST(AST_RETURN_EMPTY_T);
}


bc_AST* NewASTThrow(bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_STMT_THROW_T);
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTTry(bc_AST* abody, bc_AST* acatch_list) {
	bc_AST* ret = bc_NewAST(AST_STMT_TRY_T);
	bc_PushAST(ret, abody);
	bc_PushAST(ret, acatch_list);
	return ret;
}

bc_AST* NewASTCatch(bc_AST* stypename, StringView name, bc_AST* abody) {
	bc_AST* ret = bc_NewAST(AST_STMT_CATCH_T);
	bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	bc_PushAST(ret, stypename);
	bc_PushAST(ret, aname);
	bc_PushAST(ret, abody);
	return ret;
}

bc_AST* NewASTCatchList(bc_AST* acatch, bc_AST* acatch_list) {
	bc_AST* ret = bc_NewAST(AST_STMT_CATCH_LIST_T);
	bc_PushAST(ret, acatch);
	bc_PushAST(ret, acatch_list);
	return ret;
}

bc_AST* NewASTArgument(bc_AST* afactor) {
	bc_AST* ret = bc_NewAST(AST_ARGUMENT_T);
	bc_PushAST(ret, afactor);
	return ret;
}

bc_AST* NewASTArgumentList(bc_AST* afactor, bc_AST* aargument_list) {
	bc_AST* ret = bc_NewAST(AST_ARGUMENT_LIST_T);
	bc_PushAST(ret, aargument_list);
	bc_PushAST(ret, afactor);
	return ret;
}

bc_AST* NewASTFQCN(bc_AST* apart_list, StringView class_name) {
	bc_AST* ret = bc_NewAST(AST_FQCN_T);
	bc_AST* a = bc_NewAST(AST_FQCN_CLASS_NAME_T);
	a->Attr.StringVValue = class_name;
	bc_PushAST(ret, apart_list);
	bc_PushAST(ret, a);
	return ret;
}

bc_AST* MallocASTFQCNPart(StringView namev, const char* filename, int lineno) {
	bc_AST* ret = bc_MallocAST(AST_FQCN_PART_T, filename, lineno);
	ret->Attr.StringVValue = namev;
	return ret;
}

bc_AST* NewASTFQCNPartList(bc_AST* apart, bc_AST* apart_list) {
	bc_AST* ret = bc_NewAST(AST_FQCN_PART_LIST_T);
	bc_PushAST(ret, apart_list);
	bc_PushAST(ret, apart);
	return ret;
}

bc_AST* NewASTVariableDecl(bc_AST* atype, StringView name) {
	bc_AST* ret = bc_NewAST(AST_STMT_VARIABLE_DECL_T);
	bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	bc_PushAST(ret, atype);
	bc_PushAST(ret, aname);
	return ret;
}

bc_AST* NewASTVariableInit(bc_AST* atype, StringView name, bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_STMT_VARIABLE_INIT_T);
	bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	bc_PushAST(ret, atype);
	bc_PushAST(ret, aname);
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTInferencedTypeInit(StringView name, bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_INFERENCED_TYPE_INIT_T);
	bc_AST* aname = bc_NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	bc_PushAST(ret, aname);
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTAssert(bc_AST* afact, bc_AST* amsg) {
	bc_AST* ret = bc_NewAST(AST_STMT_ASSERT_T);
	bc_PushAST(ret, afact);
	bc_PushAST(ret, amsg);
	return ret;
}

bc_AST* NewASTDefer(bc_AST* astmt) {
	bc_AST* ret = bc_NewAST(AST_STMT_DEFER_T);
	bc_PushAST(ret, astmt);
	return ret;
}

bc_AST* NewASTYieldReturn(bc_AST* afact) {
	bc_AST* ret = bc_NewAST(AST_YIELD_RETURN_T);
	bc_PushAST(ret, afact);
	return ret;
}

bc_AST* NewASTYieldBreak() {
	return bc_NewAST(AST_YIELD_BREAK_T);
}

bc_AST* NewASTInject(StringView name, bc_AST* avalue) {
	bc_AST* ret = bc_NewAST(AST_INJECT_JNI_VALUE_T);
	ret->Attr.StringVValue = name;
	bc_PushAST(ret, avalue);
	ret->Lineno = 0;
	avalue->Lineno = 0;
	return ret;
}