#include "ast_new_literal.h"


bc_AST* NewASTInt(int i) {
	bc_AST* ret = bc_NewAST(AST_INT_T);
	ret->Attr.IntValue = i;
	return ret;
}

bc_AST* NewASTDouble(double d) {
	bc_AST* ret = bc_NewAST(AST_DOUBLE_T);
	ret->Attr.DoubleValue = d;
	return ret;
}

bc_AST* NewASTChar(char ch) {
	bc_AST* ret = bc_NewAST(AST_CHAR_T);
	ret->Attr.CharValue = ch;
	return ret;
}

bc_AST* NewASTString(StringView str) {
	bc_AST* ret = bc_NewAST(AST_STRING_T);
	ret->Attr.StringVValue = str;
	return ret;
}
