#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_return(il_stmt_return * self, Enviroment * env, CallContext* cctx);

il_stmt * WrapILReturn(il_stmt_return * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_RETURN_T);
	ret->u.return_ = self;
	return ret;
}

il_stmt_return * NewILReturn() {
	il_stmt_return* ret = (il_stmt_return*)MEM_MALLOC(sizeof(il_stmt_return));
	ret->fact = NULL;
	return ret;
}

void GenerateILReturn(il_stmt_return * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_RETURN);
}

void LoadILReturn(il_stmt_return * self, Enviroment * env, CallContext* cctx) {
	LoadILFactor(self->fact, env, cctx);
	BC_ERROR();
	check_method_return(self, env, cctx);
}

void DeleteILReturn(il_stmt_return * self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
//private
static void check_method_return(il_stmt_return * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* m = GetMethodCContext(cctx);
	//戻り値が Void なのに値を返している
	if(m->ReturnGType->CoreType == TYPE_VOID) {
		ThrowBCError(BCERROR_RETURN_VALUE_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
		return;
	}
	//戻り値の型に互換性がない
	GenericType* retT =EvalILFactor(self->fact, env, cctx);
	if(retT->CoreType != TYPE_NULL &&
	   DistanceGenericType(m->ReturnGType, retT, cctx) < 0) {
		ThrowBCError(BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
	}
}