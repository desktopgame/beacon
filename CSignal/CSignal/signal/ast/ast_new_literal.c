#include "ast_new_literal.h"


ast * ast_new_int(int i) {
	ast* ret = ast_new(ast_int);
	ret->u.int_value = i;
	return ret;
}

ast * ast_new_double(double d) {
	ast* ret = ast_new(ast_double);
	ret->u.double_value = d;
	return ret;
}

ast * ast_new_char(char ch) {
	ast* ret = ast_new(ast_char);
	ret->u.char_value = ch;
	return ret;
}

ast * ast_new_string(char * str) {
	ast* ret = ast_new(ast_string);
	ret->u.string_value = str;
	return ret;
}
