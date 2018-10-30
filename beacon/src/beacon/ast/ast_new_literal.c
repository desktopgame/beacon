#include "ast_new_literal.h"


AST* NewASTInt(int i) {
	AST* ret = NewAST(AST_INT_T);
	ret->Attr.IntValue = i;
	return ret;
}

AST* NewASTDouble(double d) {
	AST* ret = NewAST(AST_DOUBLE_T);
	ret->Attr.DoubleValue = d;
	return ret;
}

AST* NewASTChar(char ch) {
	AST* ret = NewAST(AST_CHAR_T);
	ret->Attr.CharValue = ch;
	return ret;
}

AST* NewASTString(StringView sv) {
	AST* ret = NewAST(AST_STRING_T);
	ret->Attr.StringVValue = sv;
	return ret;
}
