#include "il_stmt_yield_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_IsYieldMethod_return(ILStatement_yield_return * self, Enviroment * env, CallContext* cctx);

ILStatement* WrapILYieldReturn(ILStatement_yield_return* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_YIELD_RETURN_T);
	ret->type = ILSTMT_YIELD_RETURN_T;
	ret->u.yield_return = self;
	return ret;
}

ILStatement_yield_return* MallocILYieldReturn(const char* filename, int lineno) {
	ILStatement_yield_return* ret = (ILStatement_yield_return*)mem_malloc(sizeof(ILStatement_yield_return), filename, lineno);
	ret->fact = NULL;
	return ret;
}

void GenerateILYieldReturn(ILStatement_yield_return* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_CORO_NEXT);
}

void LoadILYieldReturn(ILStatement_yield_return * self, Enviroment* env, CallContext* cctx) {
	check_IsYieldMethod_return(self, env, cctx);
}

void DeleteILYieldReturn(ILStatement_yield_return* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
//private
static void check_IsYieldMethod_return(ILStatement_yield_return * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* m = GetMethodCContext(cctx);
	GenericType* arg = AtVector(m->ReturnGType->TypeArgs, 0);
	//戻り値の型に互換性がない
	if(DistanceGenericType(arg, EvalILFactor(self->fact, env, cctx), cctx) < 0) {
		ThrowBCError(BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
	}
}