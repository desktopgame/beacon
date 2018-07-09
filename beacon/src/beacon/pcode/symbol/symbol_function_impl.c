#include "symbol_function_impl.h"
#include "../../util/mem.h"

symbol_function* symbol_function_create_c(cell_apply a) {
	symbol_function* ret = (symbol_function*)MEM_MALLOC(sizeof(symbol_function));
	ret->tag = symbol_function_blt_T;
	ret->u.a_ = a;
	return ret;
}

symbol_function* symbol_function_create_lisp(cell* code) {
	symbol_function* ret = (symbol_function*)MEM_MALLOC(sizeof(symbol_function));
	ret->tag = symbol_function_user_T;
	ret->u.code = code;
	return ret;
}

cell* symbol_function_apply(symbol_function* func, cell* args) {
	switch(func->tag) {
		case symbol_function_blt_T:
			return func->u.a_(args);
		case symbol_function_user_T:
			return NULL;
		default:
			return cell_nil();
	}
}

void symbol_function_delete(symbol_function* self);