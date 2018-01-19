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
	ret->fqcn = fqcn_cache_new();
	return ret;
}

void il_stmt_variable_init_dump(il_stmt_variable_init * self, int depth) {
	text_putindent(depth);
	printf("variable init %s", self->name);
	text_putline();
	fqcn_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_variable_init_generate(il_stmt_variable_init * self, enviroment * env) {
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec)),
		self->name
	);
	il_factor_generate(self->fact, env);
	//éŒ¾Œ^‚Æ‘ã“üŒ^‚ªˆÙ‚È‚éê‡
	type* a = il_factor_eval(self->fact, env);
	type* b = fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec));
	if (a != b) {
		opcode_buf_add(env->buf, op_lookup);
		opcode_buf_add(env->buf, b->absoluteIndex);
	}
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, e->index);
}

void il_stmt_variable_init_load(il_stmt_variable_init * self, enviroment * env, il_ehandler * eh) {
}

void il_stmt_variable_init_delete(il_stmt_variable_init * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}
