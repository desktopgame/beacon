#include "il_stmt_variable_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <assert.h>

il_stmt * il_stmt_wrap_variable_init(il_stmt_variable_init * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->type = ilstmt_variable_init;
	ret->u.variable_init = self;
	return ret;
}

il_stmt_variable_init * il_stmt_variable_init_new(string_view namev) {
	il_stmt_variable_init* ret = (il_stmt_variable_init*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->namev = namev;
	ret->fact = NULL;
	ret->fqcn = generic_cache_new();
	return ret;
}

void il_stmt_variable_init_dump(il_stmt_variable_init * self, int depth) {
	text_putindent(depth);
	text_printf("variable init %s", string_pool_ref2str(self->namev));
	text_putline();
	generic_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_variable_init_generate(il_stmt_variable_init * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	//宣言型と代入型が異なる場合
	generic_type* ga = il_factor_eval(self->fact, env, cctx);
	generic_type* gb = import_manager_resolve(NULL, NULL, self->fqcn, cctx);
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, self->sym->index);
}

void il_stmt_variable_init_load(il_stmt_variable_init * self, enviroment * env, call_context* cctx) {
	il_factor_load(self->fact, env, cctx);
	if(symbol_table_contains(env->sym_table, self->namev)) {
		bc_error_throw(bcerror_overwrap_variable_name,
			string_pool_ref2str(self->namev)
		);
	}
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		import_manager_resolve(NULL, NULL, self->fqcn, cctx),
		self->namev
	);
	self->sym = e;
}

void il_stmt_variable_init_delete(il_stmt_variable_init * self) {
	il_factor_delete(self->fact);
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}
