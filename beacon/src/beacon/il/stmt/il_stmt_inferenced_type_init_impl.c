#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

il_stmt * il_stmt_wrap_inferenced_type_init(il_stmt_inferenced_type_init * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_INFERENCED_TYPE_INIT_T);
	ret->u.inferenced_type_init = self;
	return ret;
}

il_stmt_inferenced_type_init * il_stmt_inferenced_type_init_new(string_view namev) {
	il_stmt_inferenced_type_init* ret = (il_stmt_inferenced_type_init*)MEM_MALLOC(sizeof(il_stmt_inferenced_type_init));
	ret->namev = namev;
	ret->fact = NULL;
	return ret;
}

void il_stmt_inferenced_type_init_generate(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	//右辺の方で宣言する
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, OP_STORE);
	opcode_buf_add(env->buf, self->sym->index);
}

void il_stmt_inferenced_type_init_load(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	//代入するオブジェクトを計算
	il_factor_load(self->fact, env, cctx);
	generic_type* gtp = il_factor_eval(self->fact, env, cctx);
	BC_ERROR();
	//voidは代入できない
	if(gtp->core_type != NULL &&
	   gtp->core_type == TYPE_VOID) {
		   bc_error_throw(BCERROR_VOID_ASSIGN_T);
		return;
	}
	//変数を登録
	if(symbol_table_contains(env->sym_table, self->namev)) {
		bc_error_throw(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		gtp,
		self->namev
	);
	self->sym = e;
}

void il_stmt_inferenced_type_init_delete(il_stmt_inferenced_type_init * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
