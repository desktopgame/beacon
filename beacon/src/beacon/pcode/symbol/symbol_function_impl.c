#include "symbol_function_impl.h"
#include "../../util/mem.h"
#include <assert.h>

static void user_function_delete(user_function* self);

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

symbol_function* symbol_function_new_user(vector* parameter_vec, cell* code) {
	symbol_function* ret = symbol_function_new(symbol_function_user);
	ret->tag = symbol_function_user;
	user_function* userF = (user_function*)MEM_MALLOC(sizeof(user_function));
	ret->u.userF = userF;
	userF->parameter_vec = parameter_vec;
	userF->code = code;
	return ret;
}

cell* symbol_function_apply(symbol_function* self, cell* cArgs, tree_map* ctx) {
	//引数を計算する
	vector* args = cArgs->u.args;
	vector* ARGS = vector_new();
	for(int i=0; i<args->length; i++) {
		if(i == 0) {
			vector_push(ARGS, vector_at(args, i));
			continue;
		}
		vector_push(ARGS, cell_eval(vector_at(args, i), ctx));
	}
	//組み込み関数を実行する
	if(self->tag == symbol_function_builtin) {
		cell* ret = self->u.a(ARGS, ctx);
		vector_delete(ARGS, vector_deleter_null);
		return ret == CELL_VOID ? cArgs : ret;
	//ユーザ定義関数を実行する
	} else if(self->tag == symbol_function_user) {
		tree_map* newctx = tree_map_new();
		for(int i=1; i<ARGS->length; i++) {
			char* name = (char*)vector_at(self->u.userF->parameter_vec, i);
			cell* code = (cell*)vector_at(ARGS, i);
			symbol* s = symbol_new(symbol_variable_T);
			s->u.code = code;
			tree_map_put(newctx, name, s);
		}
		cell* ret = cell_eval(self->u.userF->code, newctx);
		tree_map_delete(newctx, tree_map_deleter_null);
		vector_delete(ARGS, vector_deleter_null);
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
	vector_delete(self->parameter_vec, vector_deleter_null);
	cell_delete(self->code);
}