#include "il_stmt_yield_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_yield_return(il_stmt_yield_return * self, enviroment * env, call_context* cctx);

il_stmt* il_stmt_wrap_yield_return(il_stmt_yield_return* self) {
	il_stmt* ret = il_stmt_new(ilstmt_yield_return_T);
	ret->type = ilstmt_yield_return_T;
	ret->u.yield_return = self;
	return ret;
}

il_stmt_yield_return* il_stmt_yield_return_malloc(const char* filename, int lineno) {
	il_stmt_yield_return* ret = (il_stmt_yield_return*)mem_malloc(sizeof(il_stmt_yield_return), filename, lineno);
	ret->fact = NULL;
	return ret;
}

void il_stmt_yield_return_generate(il_stmt_yield_return* self, enviroment* env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_coro_next);
}

void il_stmt_yield_return_load(il_stmt_yield_return * self, enviroment* env, call_context* cctx) {
	check_method_yield_return(self, env, cctx);
}

void il_stmt_yield_return_delete(il_stmt_yield_return* self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
//private
static void check_method_yield_return(il_stmt_yield_return * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != call_method_T) {
		return;
	}
	method* m = call_context_method(cctx);
	generic_type* arg = AtVector(m->return_gtype->type_args_list, 0);
	//戻り値の型に互換性がない
	if(generic_type_distance(arg, il_factor_eval(self->fact, env, cctx), cctx) < 0) {
		bc_error_throw(bcerror_yield_return_value_type_is_not_compatible_T,
			Ref2Str(type_name(m->parent)),
			Ref2Str(m->namev)
		);
	}
}