#include "ast_new_operator.h"
#include <stdlib.h>
//proto
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r);
static ast* ast_new_uop(ast_tag tag, ast* a);

ast* ast_new_unary(ast_tag tag, ast* a) {
	ast* ret = ast_new(tag);
	ast_push(ret, a);
	return ret;
}

ast* ast_new_binary(ast_tag tag, ast* left, ast* right) {
	ast* ret = ast_new(tag);
	ast_push(ret, left);
	ast_push(ret, right);
	return ret;
}
