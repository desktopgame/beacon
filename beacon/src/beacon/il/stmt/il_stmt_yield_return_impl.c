#include "il_stmt_yield_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_IsYieldMethod_return(il_stmt_yield_return * self, enviroment * env, call_context* cctx);

il_stmt* WrapILYieldReturn(il_stmt_yield_return* self) {
	il_stmt* ret = il_stmt_new(ILSTMT_YIELD_RETURN_T);
	ret->type = ILSTMT_YIELD_RETURN_T;
	ret->u.yield_return = self;
	return ret;
}

il_stmt_yield_return* MallocILYieldReturn(const char* filename, int lineno) {
	il_stmt_yield_return* ret = (il_stmt_yield_return*)mem_malloc(sizeof(il_stmt_yield_return), filename, lineno);
	ret->fact = NULL;
	return ret;
}

void GenerateILYieldReturn(il_stmt_yield_return* self, enviroment* env, call_context* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->buf, OP_CORO_NEXT);
}

void LoadILYieldReturn(il_stmt_yield_return * self, enviroment* env, call_context* cctx) {
	check_IsYieldMethod_return(self, env, cctx);
}

void DeleteILYieldReturn(il_stmt_yield_return* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
//private
static void check_IsYieldMethod_return(il_stmt_yield_return * self, enviroment * env, call_context* cctx) {
	if(cctx->tag != CALL_METHOD_T) {
		return;
	}
	method* m = GetMethodCContext(cctx);
	generic_type* arg = AtVector(m->return_gtype->type_args_list, 0);
	//戻り値の型に互換性がない
	if(DistanceGenericType(arg, EvalILFactor(self->fact, env, cctx), cctx) < 0) {
		ThrowBCError(BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T,
			Ref2Str(GetTypeName(m->parent)),
			Ref2Str(m->namev)
		);
	}
}