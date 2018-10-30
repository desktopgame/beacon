#include "ast_new_operator.h"
#include <stdlib.h>
//proto
static AST* ast_new_bop(ASTTag tag, AST* l, AST* r);
static AST* ast_new_uop(ASTTag tag, AST* a);

AST* NewASTUnary(ASTTag tag, AST* a) {
	AST* ret = NewAST(tag);
	PushAST(ret, a);
	return ret;
}

AST* NewASTBinary(ASTTag tag, AST* aleft, AST* aright) {
	AST* ret = NewAST(tag);
	PushAST(ret, aleft);
	PushAST(ret, aright);
	return ret;
}
