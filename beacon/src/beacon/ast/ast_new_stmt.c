#include "ast_new_stmt.h"

ast * MallocAST_stmt(ast * astmt, const char* filename, int lineno) {
	ast* ret = MallocAST(ast_stmt_T, filename, lineno);
	PushAST(ret, astmt);
	return ret;
}

ast * NewASTStmtList(ast * astmt, ast * astmt_list) {
	ast* ret = ast_new(ast_stmt_list_T);
	PushAST(ret, astmt);
	PushAST(ret, astmt_list);
	return ret;
}

ast * NewASTIf(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_if_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTElse(ast * abody) {
	ast* ret = ast_new(ast_else_T);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTIf_else(ast * acond, ast * atrueBody, ast * afalseBody) {
	ast* ret = ast_new(ast_if_else_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, NewASTElse(afalseBody));
	return ret;
}

ast * NewASTIfElifList(ast * acond, ast * atrueBody, ast * aelifList) {
	ast* ret = ast_new(ast_if_elif_list_T);
	PushAST(ret, NewASTIf(acond, atrueBody));
	PushAST(ret, aelifList);
	return ret;
}

ast * NewASTIfElifList_else(ast * acond, ast * atrueBody, ast * aelifList, ast * aelseBody) {
	ast* ret = ast_new(ast_if_elif_list_else_T);
	PushAST(ret, NewASTIfElifList(acond, atrueBody, aelifList));
	PushAST(ret, NewASTElse(aelseBody));
	return ret;
}

ast * NewASTElifList(ast * aforward, ast * atail) {
	ast* ret = ast_new(ast_elif_list_T);
	PushAST(ret, aforward);
	PushAST(ret, atail);
	return ret;
}

ast * NewASTElif(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_elif_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTWhile(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_while_T);
	PushAST(ret, acond);
	PushAST(ret, abody);
	return ret;
}

ast * NewASTBreak() {
	return ast_new(ast_break_T);
}

ast * NewASTContinue() {
	return ast_new(ast_continue_T);
}

ast * NewASTReturn(ast * afact) {
	ast* ret = ast_new(ast_return_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTReturnEmpty() {
	return ast_new(ast_return_empty_T);
}


ast* NewASTThrow(ast* afact) {
	ast* ret = ast_new(ast_stmt_throw_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTTry(ast* abody, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_try_T);
	PushAST(ret, abody);
	PushAST(ret, acatch_list);
	return ret;
}

ast* NewASTCatch(ast* stypename, string_view snamev, ast* abody) {
	ast* ret = ast_new(ast_stmt_catch_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = snamev;
	PushAST(ret, stypename);
	PushAST(ret, aname);
	PushAST(ret, abody);
	return ret;
}

ast* NewASTCatchList(ast* acatch, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_catch_list_T);
	PushAST(ret, acatch);
	PushAST(ret, acatch_list);
	return ret;
}

ast * NewASTArgument(ast * afactor) {
	ast* ret = ast_new(ast_argument_T);
	PushAST(ret, afactor);
	return ret;
}

ast * NewASTArgumentList(ast * afactor, ast * aargument_list) {
	ast* ret = ast_new(ast_argument_list_T);
	PushAST(ret, aargument_list);
	PushAST(ret, afactor);
	return ret;
}

ast * NewASTFQCN(ast * apart_list, string_view class_namev) {
	ast* ret = ast_new(ast_fqcn_T);
	ast* a = ast_new(ast_fqcn_class_name_T);
	a->u.stringv_value = class_namev;
	PushAST(ret, apart_list);
	PushAST(ret, a);
	return ret;
}

ast* MallocAST_fqcn_part(string_view namev, const char* filename, int lineno) {
	ast* ret = MallocAST(ast_fqcn_part_T, filename, lineno);
	ret->u.stringv_value = namev;
	return ret;
}

ast * NewASTFQCNPartList(ast * apart, ast * apart_list) {
	ast* ret = ast_new(ast_fqcn_part_list_T);
	PushAST(ret, apart_list);
	PushAST(ret, apart);
	return ret;
}

ast * NewASTVariable_decl(ast * atype, string_view namev) {
	ast* ret = ast_new(ast_stmt_variable_decl_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	PushAST(ret, atype);
	PushAST(ret, aname);
	return ret;
}

ast * NewASTVariable_init(ast * atype, string_view namev, ast * afact) {
	ast* ret = ast_new(ast_stmt_variable_init_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	PushAST(ret, atype);
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

ast * NewASTInferencedTypeInit(string_view namev, ast * afact) {
	ast* ret = ast_new(ast_inferenced_type_init_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	PushAST(ret, aname);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTAssert(ast* afact, ast* amsg) {
	ast* ret = ast_new(ast_stmt_assert_T);
	PushAST(ret, afact);
	PushAST(ret, amsg);
	return ret;
}

ast* NewASTDefer(ast* astmt) {
	ast* ret = ast_new(ast_stmt_defer_T);
	PushAST(ret, astmt);
	return ret;
}

ast* NewASTYieldReturn(ast* afact) {
	ast* ret = ast_new(ast_yield_return_T);
	PushAST(ret, afact);
	return ret;
}

ast* NewASTYieldBreak() {
	return ast_new(ast_yield_break_T);
}

ast* NewASTInject(string_view namev, ast* avalue) {
	ast* ret = ast_new(ast_inject_jni_value_T);
	ret->u.stringv_value = namev;
	PushAST(ret, avalue);
	ret->lineno = 0;
	avalue->lineno = 0;
	return ret;
}