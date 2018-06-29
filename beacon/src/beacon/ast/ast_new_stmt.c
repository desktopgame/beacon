#include "ast_new_stmt.h"

ast * ast_malloc_stmt(ast * stmt, const char* filename, int lineno) {
	ast* ret = ast_malloc(ast_stmt, filename, lineno);
	ast_push(ret, stmt);
	return ret;
}

ast * ast_new_stmt_list(ast * stmt, ast * stmt_list) {
	ast* ret = ast_new(ast_stmt_list);
	ast_push(ret, stmt);
	ast_push(ret, stmt_list);
	return ret;
}

ast * ast_new_if(ast * cond, ast * body) {
	ast* ret = ast_new(ast_if);
	ast_push(ret, cond);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_else(ast * body) {
	ast* ret = ast_new(ast_else);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_if_else(ast * cond, ast * trueBody, ast * falseBody) {
	ast* ret = ast_new(ast_if_else);
	ast_push(ret, ast_new_if(cond, trueBody));
	ast_push(ret, ast_new_else(falseBody));
	return ret;
}

ast * ast_new_if_elif_list(ast * cond, ast * trueBody, ast * elifList) {
	ast* ret = ast_new(ast_if_elif_list);
	ast_push(ret, ast_new_if(cond, trueBody));
	ast_push(ret, elifList);
	return ret;
}

ast * ast_new_if_elif_list_else(ast * cond, ast * trueBody, ast * elifList, ast * elseBody) {
	ast* ret = ast_new(ast_if_elif_list_else);
	ast_push(ret, ast_new_if_elif_list(cond, trueBody, elifList));
	ast_push(ret, ast_new_else(elseBody));
	return ret;
}

ast * ast_new_elif_list(ast * forward, ast * tail) {
	ast* ret = ast_new(ast_elif_list);
	ast_push(ret, forward);
	ast_push(ret, tail);
	return ret;
}

ast * ast_new_elif(ast * cond, ast * body) {
	ast* ret = ast_new(ast_elif);
	ast_push(ret, cond);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_while(ast * cond, ast * body) {
	ast* ret = ast_new(ast_while);
	ast_push(ret, cond);
	ast_push(ret, body);
	return ret;
}

ast * ast_new_break() {
	return ast_new(ast_break);
}

ast * ast_new_continue() {
	return ast_new(ast_continue);
}

ast * ast_new_return(ast * fact) {
	ast* ret = ast_new(ast_return);
	ast_push(ret, fact);
	return ret;
}


ast* ast_new_throw(ast* fact) {
	ast* ret = ast_new(ast_stmt_throw);
	ast_push(ret, fact);
	return ret;
}

ast* ast_new_try(ast* abody, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_try);
	ast_push(ret, abody);
	ast_push(ret, acatch_list);
	return ret;
}

ast* ast_new_catch(ast* stypename, char* sname, ast* abody) {
	ast* ret = ast_new(ast_stmt_catch);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = sname;
	ast_push(ret, stypename);
	ast_push(ret, aname);
	ast_push(ret, abody);
	return ret;
}

ast* ast_new_catch_list(ast* acatch, ast* acatch_list) {
	ast* ret = ast_new(ast_stmt_catch_list);
	ast_push(ret, acatch);
	ast_push(ret, acatch_list);
	return ret;
}

ast * ast_new_argument(ast * factor) {
	ast* ret = ast_new(ast_argument);
	ast_push(ret, factor);
	return ret;
}

ast * ast_new_argument_list(ast * factor, ast * argument_list) {
	ast* ret = ast_new(ast_argument_list);
	ast_push(ret, argument_list);
	ast_push(ret, factor);
	return ret;
}

ast * ast_new_fqcn(ast * part_list, char * class_name) {
	ast* ret = ast_new(ast_fqcn);
	ast* a = ast_new(ast_fqcn_class_name);
	a->u.string_value = class_name;
	ast_push(ret, part_list);
	ast_push(ret, a);
	return ret;
}

ast* ast_malloc_fqcn_part(char* name, const char* filename, int lineno) {
	ast* ret = ast_malloc(ast_fqcn_part, filename, lineno);
	ret->u.string_value = name;
	return ret;
}

ast * ast_new_fqcn_part_list(ast * part, ast * part_list) {
	ast* ret = ast_new(ast_fqcn_part_list);
	ast_push(ret, part_list);
	ast_push(ret, part);
	return ret;
}

ast * ast_new_variable_decl(ast * type, char * name) {
	ast* ret = ast_new(ast_stmt_variable_decl);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, type);
	ast_push(ret, aname);
	return ret;
}

ast * ast_new_variable_init(ast * type, char * name, ast * fact) {
	ast* ret = ast_new(ast_stmt_variable_init);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, type);
	ast_push(ret, aname);
	ast_push(ret, fact);
	return ret;
}

ast * ast_new_inferenced_type_init(const char * name, ast * fact) {
	ast* ret = ast_new(ast_inferenced_type_init);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, aname);
	ast_push(ret, fact);
	return ret;
}

ast* ast_new_assert(ast* afact, ast* amsg) {
	ast* ret = ast_new(ast_stmt_assert);
	ast_push(ret, afact);
	ast_push(ret, amsg);
	return ret;
}

ast* ast_new_defer(ast* astmt) {
	ast* ret = ast_new(ast_stmt_defer);
	ast_push(ret, astmt);
	return ret;
}