#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_return(il_stmt_return * self, enviroment * env, call_context* cctx);

il_stmt * il_stmt_wrap_return(il_stmt_return * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_RETURN_T);
	ret->u.return_ = self;
	return ret;
}

il_stmt_return * il_stmt_return_new() {
	il_stmt_return* ret = (il_stmt_return*)MEM_MALLOC(sizeof(il_stmt_return));
	ret->fact = NULL;
	return ret;
}

void il_stmt_return_generate(il_stmt_return * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	AddOpcodeBuf(env->buf, OP_RETURN);
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
	if(cctx->tag != CALL_METHOD_T) {
		return;
	}
	method* m = call_context_method(cctx);
	//戻り値が Void なのに値を返している
	if(m->return_gtype->core_type == TYPE_VOID) {
		bc_error_throw(BCERROR_RETURN_VALUE_VOID_METHOD_T,
			Ref2Str(type_name(m->parent)),
			Ref2Str(m->namev)
		);
		return;
	}
	//戻り値の型に互換性がない
	generic_type* retT =il_factor_eval(self->fact, env, cctx);
	if(retT->core_type != TYPE_NULL &&
	   generic_type_distance(m->return_gtype, retT, cctx) < 0) {
		bc_error_throw(BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T,
			Ref2Str(type_name(m->parent)),
			Ref2Str(m->namev)
		);
	}
}