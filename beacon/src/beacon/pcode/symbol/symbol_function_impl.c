#include "symbol_function_impl.h"
#include "../../util/mem.h"
#include <assert.h>

static void user_function_delete(user_function* self);
static void symbol_function_symbol_delete(tree_item item);
static void symbol_function_argument_delete(vector_item item);

symbol_function* symbol_function_new(symbol_function_tag tag) {
	symbol_function* ret = (symbol_function*)MEM_MALLOC(sizeof(symbol_function));
	ret->tag = tag;
	return ret;
}

symbol_function* symbol_function_new_builtin(cell_apply a) {
	symbol_function* ret = symbol_function_new(symbol_function_builtin);
	ret->tag = symbol_function_builtin;
	ret->u.a = a;
	return ret;
}

symbol_function* symbol_function_new_user(cell* params, cell* code) {
	symbol_function* ret = symbol_function_new(symbol_function_user);
	ret->tag = symbol_function_user;
	user_function* userF = (user_function*)MEM_MALLOC(sizeof(user_function));
	ret->u.userF = userF;
	userF->params = params;
	userF->code = code;
	return ret;
}

cell* symbol_function_apply(symbol_function* self, cell* cArgs, tree_map* ctx) {
	//引数を計算する
	vector* args = cArgs->u.vec;
	vector* ARGS = vector_new();
	for(int i=0; i<args->length; i++) {
		cell* e =vector_at(args, i);
		e->paint = cell_protect;
		if(i == 0) {
			e->paint = cell_protect;
			vector_push(ARGS, e);
			continue;
		}
		cell* d = cell_eval(vector_at(args, i), ctx);
		vector_push(ARGS, d);
		d->paint = cell_protect;
	}
	//組み込み関数を実行する
	if(self->tag == symbol_function_builtin) {
		tree_map* newctx = tree_map_new();
		cell* ret = self->u.a(ARGS, newctx);
		vector_delete(ARGS, symbol_function_argument_delete);
		tree_map_delete(newctx, symbol_function_symbol_delete);
		return ret == CELL_VOID ? cArgs : ret;
	//ユーザ定義関数を実行する
	} else if(self->tag == symbol_function_user) {
		cell* params = self->u.userF->params;
		cell* code = self->u.userF->code;
		tree_map* newctx = tree_map_new();
		for(int i=0; i<params->u.vec->length; i++) {
			symbol* s = symbol_new(symbol_variable_T);
			s->u.code = vector_at(ARGS, i + 1);
			tree_map_put(newctx, cell_2str(vector_at(params->u.vec, i)), s);
		}
		cell* ret = cell_eval(code, newctx);
		vector_delete(ARGS, symbol_function_argument_delete);
		tree_map_delete(newctx, symbol_function_symbol_delete);
		return ret == CELL_VOID ? cArgs : ret;
	}
	assert(false);
}

void symbol_function_delete(symbol_function* self) {
	if(self->tag == symbol_function_user) {
		user_function_delete(self->u.userF);
	}
	MEM_FREE(self);
}
//private
static void user_function_delete(user_function* self) {
	//vector_delete(self->parameter_vec, vector_deleter_null);
	cell_delete(self->params);
	cell_delete(self->code);
}

static void symbol_function_symbol_delete(tree_item item) {
	symbol* e = (symbol*)item;
	symbol_delete(e);
}

static void symbol_function_argument_delete(vector_item item) {
	cell* e = (cell*)item;
	if(e->paint == cell_protect) {
		e->paint = cell_unmark;
	}
}
