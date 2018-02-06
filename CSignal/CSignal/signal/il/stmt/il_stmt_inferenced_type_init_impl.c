#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_inferenced_type_init(il_stmt_inferenced_type_init * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_inferenced_type_init;
	ret->u.inferenced_type_init = self;
	return ret;
}

il_stmt_inferenced_type_init * il_stmt_inferenced_type_init_new(const char * name) {
	il_stmt_inferenced_type_init* ret = (il_stmt_inferenced_type_init*)MEM_MALLOC(sizeof(il_stmt_inferenced_type_init));
	ret->name = text_strdup(name);
	ret->fact = NULL;
	return ret;
}

void il_stmt_inferenced_type_init_dump(il_stmt_inferenced_type_init * self, int depth) {
	text_putindent(depth);
	text_printf("var init %s", self->name);
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_inferenced_type_init_generate(il_stmt_inferenced_type_init * self, enviroment * env) {
	//右辺の方で宣言する
	type* tp = il_factor_eval(self->fact, env);
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		tp,
//		fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec)),
		self->name
	);
	il_factor_generate(self->fact, env);
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, e->index);
}

void il_stmt_inferenced_type_init_load(il_stmt_inferenced_type_init * self, enviroment * env, il_ehandler * eh) {
}

void il_stmt_inferenced_type_init_delete(il_stmt_inferenced_type_init * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
	il_factor_delete(self->fact);
}
