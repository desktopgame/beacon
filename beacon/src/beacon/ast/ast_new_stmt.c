#include "ast_new_stmt.h"

ast * ast_malloc_stmt(ast * astmt, const char* filename, int lineno) {
	ast* ret = ast_malloc(ast_stmt_T, filename, lineno);
	ast_push(ret, astmt);
	return ret;
}

ast * ast_new_stmt_list(ast * astmt, ast * astmt_list) {
	ast* ret = ast_new(ast_stmt_list_T);
	ast_push(ret, astmt);
	ast_push(ret, astmt_list);
	return ret;
}

ast * ast_new_if(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_if_T);
	ast_push(ret, acond);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_else(ast * abody) {
	ast* ret = ast_new(ast_else_T);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_if_else(ast * acond, ast * atrueBody, ast * afalseBody) {
	ast* ret = ast_new(ast_if_else_T);
	ast_push(ret, ast_new_if(acond, atrueBody));
	ast_push(ret, ast_new_else(afalseBody));
	return ret;
}

ast * ast_new_if_elif_list(ast * acond, ast * atrueBody, ast * aelifList) {
	ast* ret = ast_new(ast_if_elif_list_T);
	ast_push(ret, ast_new_if(acond, atrueBody));
	ast_push(ret, aelifList);
	return ret;
}

ast * ast_new_if_elif_list_else(ast * acond, ast * atrueBody, ast * aelifList, ast * aelseBody) {
	ast* ret = ast_new(ast_if_elif_list_else_T);
	ast_push(ret, ast_new_if_elif_list(acond, atrueBody, aelifList));
	ast_push(ret, ast_new_else(aelseBody));
	return ret;
}

ast * ast_new_elif_list(ast * aforward, ast * atail) {
	ast* ret = ast_new(ast_elif_list_T);
	ast_push(ret, aforward);
	ast_push(ret, atail);
	return ret;
}

ast * ast_new_elif(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_elif_T);
	ast_push(ret, acond);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_while(ast * acond, ast * abody) {
	ast* ret = ast_new(ast_while_T);
	ast_push(ret, acond);
	ast_push(ret, abody);
	return ret;
}

ast * ast_new_break() {
	return ast_new(ast_break_T);
}

ast * ast_new_continue() {
	return ast_new(ast_continue_T);
}

ast * ast_new_return(ast * afact) {
	ast* ret = ast_new(ast_return_T);
	ast_push(ret, afact);
	return ret;
}

ast* ast_new_return_empty() {
	return ast_new(ast_return_empty_T);
}


ast* ast_new_throw(ast* afact) {
	ast* ret = ast_new(ast_stmt_throw_T);
	ast_push(ret, afact);
	return ret;
}

ast* ast_new_try(ast* abody, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_try_T);
	ast_push(ret, abody);
	ast_push(ret, acatch_list);
	return ret;
}

ast* ast_new_catch(ast* stypename, string_view snamev, ast* abody) {
	ast* ret = ast_new(ast_stmt_catch_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = snamev;
	ast_push(ret, stypename);
	ast_push(ret, aname);
	ast_push(ret, abody);
	return ret;
}

ast* ast_new_catch_list(ast* acatch, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_catch_list_T);
	ast_push(ret, acatch);
	ast_push(ret, acatch_list);
	return ret;
}

ast * ast_new_argument(ast * afactor) {
	ast* ret = ast_new(ast_argument_T);
	ast_push(ret, afactor);
	return ret;
}

ast * ast_new_argument_list(ast * afactor, ast * aargument_list) {
	ast* ret = ast_new(ast_argument_list_T);
	ast_push(ret, aargument_list);
	ast_push(ret, afactor);
	return ret;
}

ast * ast_new_fqcn(ast * apart_list, string_view class_namev) {
	ast* ret = ast_new(ast_fqcn_T);
	ast* a = ast_new(ast_fqcn_class_name_T);
	a->u.stringv_value = class_namev;
	ast_push(ret, apart_list);
	ast_push(ret, a);
	return ret;
}

ast* ast_malloc_fqcn_part(string_view namev, const char* filename, int lineno) {
	ast* ret = ast_malloc(ast_fqcn_part_T, filename, lineno);
	ret->u.stringv_value = namev;
	return ret;
}

ast * ast_new_fqcn_part_list(ast * apart, ast * apart_list) {
	ast* ret = ast_new(ast_fqcn_part_list_T);
	ast_push(ret, apart_list);
	ast_push(ret, apart);
	return ret;
}

ast * ast_new_variable_decl(ast * atype, string_view namev) {
	ast* ret = ast_new(ast_stmt_variable_decl_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	ast_push(ret, atype);
	ast_push(ret, aname);
	return ret;
}

ast * ast_new_variable_init(ast * atype, string_view namev, ast * afact) {
	ast* ret = ast_new(ast_stmt_variable_init_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	ast_push(ret, atype);
	ast_push(ret, aname);
	ast_push(ret, afact);
	return ret;
}

ast * ast_new_inferenced_type_init(string_view namev, ast * afact) {
	ast* ret = ast_new(ast_inferenced_type_init_T);
	ast* aname = ast_new(ast_identifier_T);
	aname->u.stringv_value = namev;
	ast_push(ret, aname);
	ast_push(ret, afact);
	return ret;
}

ast* ast_new_assert(ast* afact, ast* amsg) {
	ast* ret = ast_new(ast_stmt_assert_T);
	ast_push(ret, afact);
	ast_push(ret, amsg);
	return ret;
}

ast* ast_new_defer(ast* astmt) {
	ast* ret = ast_new(ast_stmt_defer_T);
	ast_push(ret, astmt);
	return ret;
}

ast* ast_new_yield_return(ast* afact) {
	ast* ret = ast_new(ast_yield_return_T);
	ast_push(ret, afact);
	return ret;
}

ast* ast_new_yield_break() {
	return ast_new(ast_yield_break_T);
}

ast* ast_new_inject(string_view namev, ast* avalue) {
	ast* ret = ast_new(ast_inject_jni_value_T);
	ret->u.stringv_value = namev;
	ast_push(ret, avalue);
	ret->lineno = 0;
	avalue->lineno = 0;
	return ret;
}