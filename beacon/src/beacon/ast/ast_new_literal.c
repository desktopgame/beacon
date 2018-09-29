#include "ast_new_literal.h"


ast * NewASTInt(int i) {
	ast* ret = ast_new(ast_int_T);
	ret->u.int_value = i;
	return ret;
}

ast * NewASTDouble(double d) {
	ast* ret = ast_new(ast_double_T);
	ret->u.double_value = d;
	return ret;
}

ast * NewASTChar(char ch) {
	ast* ret = ast_new(ast_char_T);
	ret->u.char_value = ch;
	return ret;
}

ast * NewASTString(string_view sv) {
	ast* ret = ast_new(ast_string_T);
	ret->u.stringv_value = sv;
	return ret;
}
