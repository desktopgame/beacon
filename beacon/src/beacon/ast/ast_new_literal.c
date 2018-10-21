#include "ast_new_literal.h"


AST* NewASTInt(int i) {
	AST* ret = ast_new(AST_INT_T);
	ret->Attr.IntValue = i;
	return ret;
}

AST* NewASTDouble(double d) {
	AST* ret = ast_new(AST_DOUBLE_T);
	ret->Attr.DoubleValue = d;
	return ret;
}

AST* NewASTChar(char ch) {
	AST* ret = ast_new(AST_CHAR_T);
	ret->Attr.CharValue = ch;
	return ret;
}

AST* NewASTString(StringView sv) {
	AST* ret = ast_new(AST_STRING_T);
	ret->Attr.StringVValue = sv;
	return ret;
}
