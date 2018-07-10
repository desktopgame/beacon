#include "symbol_function_impl.h"
#include "../../util/mem.h"
#include "../cell.h"

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

cell* symbol_function_apply(symbol_function* func, cell* args, tree_map* ctx) {
	switch(func->tag) {
		case symbol_function_blt_T:
			return func->u.a_(args, ctx);
		case symbol_function_user_T:
		{
			cell* code = func->u.code;
			cell* cname = cell_at(code, 0);
			cell* cparam = cell_at(code, 1);
			cell* cstmts = cell_at(code, 2);
			cell* ret = cstmts;
			tree_map* ctx = cell_2map(cparam, args, ctx);
			while(cstmts != NULL) {
				ret = cell_scoped_eval(cstmts->u.first, ctx);
				cstmts = cstmts->rest;
			}
			tree_map_delete(ctx, tree_map_deleter_null);
			return ret;
		}
		default:
			return cell_nil();
	}
}

void symbol_function_delete(symbol_function* self);