#include "ast_new_literal.h"


ast * NewASTInt(int i) {
	ast* ret = ast_new(AST_INT_T);
	ret->u.int_value = i;
	return ret;
}

ast * NewASTDouble(double d) {
	ast* ret = ast_new(AST_DOUBLE_T);
	ret->u.double_value = d;
	return ret;
}

ast * NewASTChar(char ch) {
	ast* ret = ast_new(AST_CHAR_T);
	ret->u.char_value = ch;
	return ret;
}

ast * NewASTString(StringView sv) {
	ast* ret = ast_new(AST_STRING_T);
	ret->u.stringv_value = sv;
	return ret;
}
