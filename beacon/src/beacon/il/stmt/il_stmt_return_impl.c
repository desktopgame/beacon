#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_return(ILReturn * self, bc_Enviroment * env, CallContext* cctx);

ILStatement * WrapILReturn(ILReturn * self) {
	ILStatement* ret = NewILStatement(ILSTMT_RETURN_T);
	ret->Kind.Return = self;
	return ret;
}

ILReturn * NewILReturn() {
	ILReturn* ret = (ILReturn*)MEM_MALLOC(sizeof(ILReturn));
	ret->Factor = NULL;
	return ret;
}

void GenerateILReturn(ILReturn * self, bc_Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->Factor, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_RETURN);
}

void LoadILReturn(ILReturn * self, bc_Enviroment * env, CallContext* cctx) {
	LoadILFactor(self->Factor, env, cctx);
	BC_ERROR();
	check_method_return(self, env, cctx);
}

void DeleteILReturn(ILReturn * self) {
	DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
//private
static void check_method_return(ILReturn * self, bc_Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	bc_Method* m = GetMethodCContext(cctx);
	//戻り値が Void なのに値を返している
	if(m->ReturnGType->CoreType == BC_TYPE_VOID) {
		bc_Panic(BCERROR_RETURN_VALUE_VOID_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(m->Parent)),
			bc_Ref2Str(m->Name)
		);
		return;
	}
	//戻り値の型に互換性がない
	bc_GenericType* retT =EvalILFactor(self->Factor, env, cctx);
	if(retT->CoreType != BC_TYPE_NULL &&
	   bc_DistanceGenericType(m->ReturnGType, retT, cctx) < 0) {
		bc_Panic(BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(m->Parent)),
			bc_Ref2Str(m->Name)
		);
	}
}