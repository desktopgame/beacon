#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_return(il_stmt_return * self, enviroment * env, call_context* cctx);

il_stmt * il_stmt_wrap_return(il_stmt_return * self) {
	il_stmt* ret = il_stmt_new(ilstmt_return);
	ret->u.return_ = self;
	return ret;
}

il_stmt_return * il_stmt_return_new() {
	il_stmt_return* ret = (il_stmt_return*)MEM_MALLOC(sizeof(il_stmt_return));
	ret->fact = NULL;
	return ret;
}

void il_stmt_return_dump(il_stmt_return * self, int depth) {
	io_printi(depth);
	printf("return");
	io_println();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_return_generate(il_stmt_return * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_return);
}

void il_stmt_return_load(il_stmt_return * self, enviroment * env, call_context* cctx) {
	il_factor_load(self->fact, env, cctx);
	BC_ERROR();
	check_method_return(self, env, cctx);
}

void il_stmt_return_delete(il_stmt_return * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
//private
static void check_method_return(il_stmt_return * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != call_method_T) {
		return;
	}
	method* m = call_context_method(cctx);
	//戻り値が Void なのに値を返している
	if(m->return_gtype->core_type == TYPE_VOID) {
		bc_error_throw(bcerror_return_value_void_method,
			string_pool_ref2str(type_name(m->parent)),
			string_pool_ref2str(m->namev)
		);
		return;
	}
	//戻り値の型に互換性がない
	generic_type* retT =il_factor_eval(self->fact, env, cctx);
	if(retT->core_type != TYPE_NULL &&
	   generic_type_distance(m->return_gtype, retT) < 0) {
		bc_error_throw(bcerror_return_value_type_is_not_compatible_not_void_method,
			string_pool_ref2str(type_name(m->parent)),
			string_pool_ref2str(m->namev)
		);
	}
}