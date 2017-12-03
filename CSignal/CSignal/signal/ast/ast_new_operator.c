#include "ast_new_operator.h"
//proto
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r);

ast * ast_new_add(ast * l, ast * r) {
	return ast_new_bop(ast_add, l, r);
}

ast * ast_new_sub(ast * l, ast * r) {
	return ast_new_bop(ast_sub, l, r);
}

ast * ast_new_mul(ast * l, ast * r) {
	return ast_new_bop(ast_mul, l, r);
}

ast * ast_new_div(ast * l, ast * r) {
	return ast_new_bop(ast_div, l, r);
}

ast * ast_new_mod(ast * l, ast * r) {
	return ast_new_bop(ast_mod, l, r);
}

//private
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r) {
	ast* ret = ast_new(tag);
	ast_push(ret, l);
	ast_push(ret, r);
	return ret;
}