#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

il_stmt * il_stmt_wrap_inferenced_type_init(il_stmt_inferenced_type_init * self) {
	il_stmt* ret = il_stmt_new(ilstmt_inferenced_type_init);
	ret->u.inferenced_type_init = self;
	return ret;
}

il_stmt_inferenced_type_init * il_stmt_inferenced_type_init_new(string_view namev) {
	il_stmt_inferenced_type_init* ret = (il_stmt_inferenced_type_init*)MEM_MALLOC(sizeof(il_stmt_inferenced_type_init));
	ret->namev = namev;
	ret->fact = NULL;
	return ret;
}

void il_stmt_inferenced_type_init_dump(il_stmt_inferenced_type_init * self, int depth) {
	text_putindent(depth);
	text_printf("var init %s", string_pool_ref2str(self->namev));
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_inferenced_type_init_generate(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	//右辺の方で宣言する
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, self->sym->index);
}

void il_stmt_inferenced_type_init_load(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	il_factor_load(self->fact, env, cctx);
	generic_type* gtp = il_factor_eval(self->fact, env, cctx);
	if(il_error_panic()) {
		return;
	}
	if(gtp->type_args_list->length > 0) {
		generic_type* a = (generic_type*)vector_at(gtp->type_args_list, 0);
		int x = 0;
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
