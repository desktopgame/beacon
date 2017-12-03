#include "ast_new_stmt.h"

ast * ast_new_variable_decl(ast * type_name, ast * identifier, ast * expr) {
	ast* ret = ast_new(ast_variable_decl);
	ast_push(ret, type_name);
	ast_push(ret, identifier);
	ast_push(ret, expr);
	return ret;
}
