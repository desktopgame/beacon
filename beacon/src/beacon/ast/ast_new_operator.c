#include "ast_new_operator.h"
#include <stdlib.h>
//proto
static bc_AST* ast_new_bop(bc_ASTTag tag, bc_AST* l, bc_AST* r);
static bc_AST* ast_new_uop(bc_ASTTag tag, bc_AST* a);

bc_AST* NewASTUnary(bc_ASTTag tag, bc_AST* a) {
	bc_AST* ret = bc_NewAST(tag);
	bc_PushAST(ret, a);
	return ret;
}

bc_AST* NewASTBinary(bc_ASTTag tag, bc_AST* aleft, bc_AST* aright) {
	bc_AST* ret = bc_NewAST(tag);
	bc_PushAST(ret, aleft);
	bc_PushAST(ret, aright);
	return ret;
}
