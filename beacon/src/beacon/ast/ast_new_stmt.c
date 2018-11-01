#include "ast_new_stmt.h"

AST* MallocASTStmt(AST* astmt, const char* filename, int lineno) {
	AST* ret = MallocAST(AST_STMT_T, filename, lineno);
	PushAST(ret, astmt);
	return ret;
}

AST* NewASTStmtList(AST* astmt, AST* astmt_list) {
	AST* ret = NewAST(AST_STMT_LIST_T);
	PushAST(ret, astmt);
	PushAST(ret, astmt_list);
	return ret;
}

AST* NewASTIf(AST* acond, AST* abody) {
	AST* ret = NewAST(AST_IF_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTElse(AST* abody) {
	AST* ret = NewAST(AST_ELSE_T);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTIfElse(AST* acond, AST* atrueBody, AST* afalseBody) {
	AST* ret = NewAST(AST_IF_ELSE_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, NewASTElse(afalseBody));
	return ret;
}

AST* NewASTIfElifList(AST* acond, AST* atrueBody, AST* aelifList) {
	AST* ret = NewAST(AST_IF_ELIF_LIST_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, aelifList);
	return ret;
}

AST* NewASTIfElifListElse(AST* acond, AST* atrueBody, AST* aelifList, AST* aelseBody) {
	AST* ret = NewAST(AST_IF_ELIF_LIST_ELSE_T);
	PushAST(ret, NewASTIfElifList(acond, atrueBody, aelifList));
	PushAST(ret, NewASTElse(aelseBody));
	return ret;
}

AST* NewASTElifList(AST* aforward, AST* atail) {
	AST* ret = NewAST(AST_ELIF_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, atail);
	return ret;
}

AST* NewASTElif(AST* acond, AST* abody) {
	AST* ret = NewAST(AST_ELIF_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTWhile(AST* acond, AST* abody) {
	AST* ret = NewAST(AST_WHILE_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTBreak() {
	return NewAST(AST_BREAK_T);
}

AST* NewASTContinue() {
	return NewAST(AST_CONTINUE_T);
}

AST* NewASTReturn(AST* afact) {
	AST* ret = NewAST(AST_RETURN_T);
	PushAST(ret, afact);
	return ret;
}

AST* NewASTReturnEmpty() {
	return NewAST(AST_RETURN_EMPTY_T);
}


AST* NewASTThrow(AST* afact) {
	AST* ret = NewAST(AST_STMT_THROW_T);
	PushAST(ret, afact);
	return ret;
}

AST* NewASTTry(AST* abody, AST* acatch_list) {
	AST* ret = NewAST(AST_STMT_TRY_T);
	PushAST(ret, abody);
	PushAST(ret, acatch_list);
	return ret;
}

AST* NewASTCatch(AST* stypename, StringView name, AST* abody) {
	AST* ret = NewAST(AST_STMT_CATCH_T);
	AST* aname = NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	PushAST(ret, stypename);
	PushAST(ret, aname);
	PushAST(ret, abody);
	return ret;
}

AST* NewASTCatchList(AST* acatch, AST* acatch_list) {
	AST* ret = NewAST(AST_STMT_CATCH_LIST_T);
	PushAST(ret, acatch);
	PushAST(ret, acatch_list);
	return ret;
}

AST* NewASTArgument(AST* afactor) {
	AST* ret = NewAST(AST_ARGUMENT_T);
	PushAST(ret, afactor);
	return ret;
}

AST* NewASTArgumentList(AST* afactor, AST* aargument_list) {
	AST* ret = NewAST(AST_ARGUMENT_LIST_T);
	PushAST(ret, aargument_list);
	PushAST(ret, afactor);
	return ret;
}

AST* NewASTFQCN(AST* apart_list, StringView class_name) {
	AST* ret = NewAST(AST_FQCN_T);
	AST* a = NewAST(AST_FQCN_CLASS_NAME_T);
	a->Attr.StringVValue = class_name;
	PushAST(ret, apart_list);
	PushAST(ret, a);
	return ret;
}

AST* MallocASTFQCNPart(StringView namev, const char* filename, int lineno) {
	AST* ret = MallocAST(AST_FQCN_PART_T, filename, lineno);
	ret->Attr.StringVValue = namev;
	return ret;
}

AST* NewASTFQCNPartList(AST* apart, AST* apart_list) {
	AST* ret = NewAST(AST_FQCN_PART_LIST_T);
	PushAST(ret, apart_list);
	PushAST(ret, apart);
	return ret;
}

AST* NewASTVariableDecl(AST* atype, StringView name) {
	AST* ret = NewAST(AST_STMT_VARIABLE_DECL_T);
	AST* aname = NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	PushAST(ret, atype);
	PushAST(ret, aname);
	return ret;
}

AST* NewASTVariableInit(AST* atype, StringView name, AST* afact) {
	AST* ret = NewAST(AST_STMT_VARIABLE_INIT_T);
	AST* aname = NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	PushAST(ret, atype);
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

AST* NewASTInferencedTypeInit(StringView name, AST* afact) {
	AST* ret = NewAST(AST_INFERENCED_TYPE_INIT_T);
	AST* aname = NewAST(AST_IDENTIFIER_T);
	aname->Attr.StringVValue = name;
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

AST* NewASTAssert(AST* afact, AST* amsg) {
	AST* ret = NewAST(AST_STMT_ASSERT_T);
	PushAST(ret, afact);
	PushAST(ret, amsg);
	return ret;
}

AST* NewASTDefer(AST* astmt) {
	AST* ret = NewAST(AST_STMT_DEFER_T);
	PushAST(ret, astmt);
	return ret;
}

AST* NewASTYieldReturn(AST* afact) {
	AST* ret = NewAST(AST_YIELD_RETURN_T);
	PushAST(ret, afact);
	return ret;
}

AST* NewASTYieldBreak() {
	return NewAST(AST_YIELD_BREAK_T);
}

AST* NewASTInject(StringView name, AST* avalue) {
	AST* ret = NewAST(AST_INJECT_JNI_VALUE_T);
	ret->Attr.StringVValue = name;
	PushAST(ret, avalue);
	ret->Lineno = 0;
	avalue->Lineno = 0;
	return ret;
}