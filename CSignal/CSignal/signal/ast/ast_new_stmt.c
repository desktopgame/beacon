#include "ast_new_stmt.h"

ast * ast_new_variable_decl(ast * type_name, ast * identifier, ast * expr) {
	ast* ret = ast_new(ast_variable_decl);
	ast_push(ret, type_name);
	ast_push(ret, identifier);
	ast_push(ret, expr);
	return ret;
}

ast * ast_new_stmt(ast * stmt) {
	ast* ret = ast_new(ast_stmt);
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
