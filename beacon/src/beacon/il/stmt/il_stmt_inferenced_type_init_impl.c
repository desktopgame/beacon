#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/xassert.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

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

void il_stmt_inferenced_type_init_generate(il_stmt_inferenced_type_init * self, enviroment * env, il_context* ilctx) {
	//右辺の方で宣言する
	il_factor_generate(self->fact, env, ilctx);
	/*
	if (gtp == CL_INT->generic_self ||
		gtp == CL_DOUBLE->generic_self ||
		gtp == CL_BOOL->generic_self ||
		gtp == CL_CHAR->generic_self) {
		//複製を代入する
		opcode_buf_add(env->buf, op_copy);
		opcode_buf_add(env->buf, op_swap);
		opcode_buf_add(env->buf, op_pop);
	}
	*/
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, self->sym->index);
}

void il_stmt_inferenced_type_init_load(il_stmt_inferenced_type_init * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
	il_factor_load(self->fact, env, ilctx, eh);
	//XSTREQ(self->name, "viter");
	XSTREQ(self->name, "xv");
	generic_type* gtp = il_factor_eval(self->fact, env, ilctx);
	if(il_error_panic()) {
		return;
	}
	generic_type_validate(gtp);
	if(gtp->type_args_list->length > 0) {
		generic_type* a = (generic_type*)vector_at(gtp->type_args_list, 0);
		int x = 0;
	}
	symbol_entry* e = symbol_table_entry(
		env->sym_table,
		gtp,
//		fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec)),
		self->name
	);
	self->sym = e;
//	XSTREQ(self->name, "st");
}

void il_stmt_inferenced_type_init_delete(il_stmt_inferenced_type_init * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
	il_factor_delete(self->fact);
}
