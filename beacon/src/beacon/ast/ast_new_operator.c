#include "ast_new_operator.h"
#include <stdlib.h>
//proto
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r);
static ast* ast_new_uop(ast_tag tag, ast* a);

ast* NewASTUnary(ast_tag tag, ast* a) {
	ast* ret = ast_new(tag);
	PushAST(ret, a);
	return ret;
}

ast* NewASTBinary(ast_tag tag, ast* aleft, ast* aright) {
	ast* ret = ast_new(tag);
	PushAST(ret, aleft);
	PushAST(ret, aright);
	return ret;
}
