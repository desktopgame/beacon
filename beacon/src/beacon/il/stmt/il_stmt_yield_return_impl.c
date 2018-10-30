#include "il_stmt_yield_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_IsYieldMethod_return(ILYieldReturn * self, Enviroment * env, CallContext* cctx);

ILStatement* WrapILYieldReturn(ILYieldReturn* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_YIELD_RETURN_T);
	ret->Type = ILSTMT_YIELD_RETURN_T;
	ret->Kind.YieldReturn = self;
	return ret;
}

ILYieldReturn* MallocILYieldReturn(const char* filename, int lineno) {
	ILYieldReturn* ret = (ILYieldReturn*)mem_malloc(sizeof(ILYieldReturn), filename, lineno);
	ret->Value = NULL;
	return ret;
}

void GenerateILYieldReturn(ILYieldReturn* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Value, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_CORO_NEXT);
}

void LoadILYieldReturn(ILYieldReturn * self, Enviroment* env, CallContext* cctx) {
	check_IsYieldMethod_return(self, env, cctx);
}

void DeleteILYieldReturn(ILYieldReturn* self) {
	DeleteILFactor(self->Value);
	MEM_FREE(self);
}
//private
static void check_IsYieldMethod_return(ILYieldReturn * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* m = GetMethodCContext(cctx);
	GenericType* arg = AtVector(m->ReturnGType->TypeArgs, 0);
	//戻り値の型に互換性がない
	if(DistanceGenericType(arg, EvalILFactor(self->Value, env, cctx), cctx) < 0) {
		ThrowBCError(BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
	}
}