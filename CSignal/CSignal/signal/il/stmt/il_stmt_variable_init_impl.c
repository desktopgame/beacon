#include "il_stmt_variable_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_variable_init(il_stmt_variable_init * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->type = ilstmt_variable_init;
	ret->u.variable_init = self;
	return ret;
}

il_stmt_variable_init * il_stmt_variable_init_new(const char * name) {
	il_stmt_variable_init* ret = (il_stmt_variable_init*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->name = text_strdup(name);
	ret->fact = NULL;
	ret->fqcn = generic_cache_new();
	return ret;
}

void il_stmt_variable_init_dump(il_stmt_variable_init * self, int depth) {
	text_putindent(depth);
	text_printf("variable init %s", self->name);
	text_putline();
	fqcn_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_variable_init_generate(il_stmt_variable_init * self, enviroment * env, il_load_cache* cache) {
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		fqcn_type(self->fqcn, (namespace_*)vector_top(cache->namespace_vec)),
		self->name
	);
	il_factor_generate(self->fact, env, cache);
	//宣言型と代入型が異なる場合
	type* a = il_factor_eval(self->fact, env, cache);
	type* b = fqcn_type(self->fqcn, (namespace_*)vector_top(cache->namespace_vec));
	if (a != b) {
		opcode_buf_add(env->buf, op_lookup);
		opcode_buf_add(env->buf, b->absolute_index);
	}
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, e->index);
}

void il_stmt_variable_init_load(il_stmt_variable_init * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
}

void il_stmt_variable_init_delete(il_stmt_variable_init * self) {
	il_factor_delete(self->fact);
	generic_cache_delete(self->fqcn);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
