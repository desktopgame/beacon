#include "ast_new_stmt.h"

ast * MallocASTStmt(ast * astmt, const char* filename, int lineno) {
	ast* ret = MallocAST(AST_STMT_T, filename, lineno);
	PushAST(ret, astmt);
	return ret;
}

ast * NewASTStmtList(ast * astmt, ast * astmt_list) {
	ast* ret = ast_new(AST_STMT_LIST_T);
	PushAST(ret, astmt);
	PushAST(ret, astmt_list);
	return ret;
}

ast * NewASTIf(ast * acond, ast * abody) {
	ast* ret = ast_new(AST_IF_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTElse(ast * abody) {
	ast* ret = ast_new(AST_ELSE_T);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTIfElse(ast * acond, ast * atrueBody, ast * afalseBody) {
	ast* ret = ast_new(AST_IF_ELSE_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, NewASTElse(afalseBody));
	return ret;
}

ast * NewASTIfElifList(ast * acond, ast * atrueBody, ast * aelifList) {
	ast* ret = ast_new(AST_IF_ELIF_LIST_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, aelifList);
	return ret;
}

ast * NewASTIfElifListElse(ast * acond, ast * atrueBody, ast * aelifList, ast * aelseBody) {
	ast* ret = ast_new(AST_IF_ELIF_LIST_ELSE_T);
	PushAST(ret, NewASTIfElifList(acond, atrueBody, aelifList));
	PushAST(ret, NewASTElse(aelseBody));
	return ret;
}

ast * NewASTElifList(ast * aforward, ast * atail) {
	ast* ret = ast_new(AST_ELIF_LIST_T);
	PushAST(ret, aforward);
	PushAST(ret, atail);
	return ret;
}

ast * NewASTElif(ast * acond, ast * abody) {
	ast* ret = ast_new(AST_ELIF_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTWhile(ast * acond, ast * abody) {
	ast* ret = ast_new(AST_WHILE_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTBreak() {
	return ast_new(AST_BREAK_T);
}

ast * NewASTContinue() {
	return ast_new(AST_CONTINUE_T);
}

ast * NewASTReturn(ast * afact) {
	ast* ret = ast_new(AST_RETURN_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTReturnEmpty() {
	return ast_new(AST_RETURN_EMPTY_T);
}


ast* NewASTThrow(ast* afact) {
	ast* ret = ast_new(AST_STMT_THROW_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTTry(ast* abody, ast* acatch_list) {
	ast* ret = ast_new(AST_STMT_TRY_T);
	PushAST(ret, abody);
	PushAST(ret, acatch_list);
	return ret;
}

ast* NewASTCatch(ast* stypename, StringView snamev, ast* abody) {
	ast* ret = ast_new(AST_STMT_CATCH_T);
	ast* aname = ast_new(AST_IDENTIFIER_T);
	aname->u.stringv_value = snamev;
	PushAST(ret, stypename);
	PushAST(ret, aname);
	PushAST(ret, abody);
	return ret;
}

ast* NewASTCatchList(ast* acatch, ast* acatch_list) {
	ast* ret = ast_new(AST_STMT_CATCH_LIST_T);
	PushAST(ret, acatch);
	PushAST(ret, acatch_list);
	return ret;
}

ast * NewASTArgument(ast * afactor) {
	ast* ret = ast_new(AST_ARGUMENT_T);
	PushAST(ret, afactor);
	return ret;
}

ast * NewASTArgumentList(ast * afactor, ast * aargument_list) {
	ast* ret = ast_new(AST_ARGUMENT_LIST_T);
	PushAST(ret, aargument_list);
	PushAST(ret, afactor);
	return ret;
}

ast * NewASTFQCN(ast * apart_list, StringView class_namev) {
	ast* ret = ast_new(AST_FQCN_T);
	ast* a = ast_new(AST_FQCN_CLASS_NAME_T);
	a->u.stringv_value = class_namev;
	PushAST(ret, apart_list);
	PushAST(ret, a);
	return ret;
}

ast* MallocASTFQCNPart(StringView namev, const char* filename, int lineno) {
	ast* ret = MallocAST(AST_FQCN_PART_T, filename, lineno);
	ret->u.stringv_value = namev;
	return ret;
}

ast * NewASTFQCNPartList(ast * apart, ast * apart_list) {
	ast* ret = ast_new(AST_FQCN_PART_LIST_T);
	PushAST(ret, apart_list);
	PushAST(ret, apart);
	return ret;
}

ast * NewASTVariableDecl(ast * atype, StringView namev) {
	ast* ret = ast_new(AST_STMT_VARIABLE_DECL_T);
	ast* aname = ast_new(AST_IDENTIFIER_T);
	aname->u.stringv_value = namev;
	PushAST(ret, atype);
	PushAST(ret, aname);
	return ret;
}

ast * NewASTVariableInit(ast * atype, StringView namev, ast * afact) {
	ast* ret = ast_new(AST_STMT_VARIABLE_INIT_T);
	ast* aname = ast_new(AST_IDENTIFIER_T);
	aname->u.stringv_value = namev;
	PushAST(ret, atype);
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

ast * NewASTInferencedTypeInit(StringView namev, ast * afact) {
	ast* ret = ast_new(AST_INFERENCED_TYPE_INIT_T);
	ast* aname = ast_new(AST_IDENTIFIER_T);
	aname->u.stringv_value = namev;
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTAssert(ast* afact, ast* amsg) {
	ast* ret = ast_new(AST_STMT_ASSERT_T);
	PushAST(ret, afact);
	PushAST(ret, amsg);
	return ret;
}

ast* NewASTDefer(ast* astmt) {
	ast* ret = ast_new(AST_STMT_DEFER_T);
	PushAST(ret, astmt);
	return ret;
}

ast* NewASTYieldReturn(ast* afact) {
	ast* ret = ast_new(AST_YIELD_RETURN_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTYieldBreak() {
	return ast_new(AST_YIELD_BREAK_T);
}

ast* NewASTInject(StringView namev, ast* avalue) {
	ast* ret = ast_new(AST_INJECT_JNI_VALUE_T);
	ret->u.stringv_value = namev;
	PushAST(ret, avalue);
	ret->lineno = 0;
	avalue->lineno = 0;
	return ret;
}