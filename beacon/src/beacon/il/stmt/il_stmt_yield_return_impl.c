#include "il_stmt_yield_return_impl.h"
#include <stdio.h>
#include "../../env/method.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"

static void check_IsYieldMethod_return(bc_ILYieldReturn* self,
                                       bc_Enviroment* env,
                                       bc_CallContext* cctx);

bc_ILStatement* bc_WrapILYieldReturn(bc_ILYieldReturn* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_YIELD_RETURN_T);
        ret->Type = ILSTMT_YIELD_RETURN_T;
        ret->Kind.YieldReturn = self;
        return ret;
}

bc_ILYieldReturn* bc_MallocILYieldReturn(const char* filename, int lineno) {
        bc_ILYieldReturn* ret = (bc_ILYieldReturn*)bc_MXMalloc(
            sizeof(bc_ILYieldReturn), filename, lineno);
        ret->Value = NULL;
        return ret;
}

void bc_GenerateILYieldReturn(bc_ILYieldReturn* self, bc_Enviroment* env,
                              bc_CallContext* cctx) {
        bc_GenerateILFactor(self->Value, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_CORO_NEXT);
}

void bc_LoadILYieldReturn(bc_ILYieldReturn* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        check_IsYieldMethod_return(self, env, cctx);
}

void bc_DeleteILYieldReturn(bc_ILYieldReturn* self) {
        bc_DeleteILFactor(self->Value);
        MEM_FREE(self);
}
// private
static void check_IsYieldMethod_return(bc_ILYieldReturn* self,
                                       bc_Enviroment* env,
                                       bc_CallContext* cctx) {
        if (cctx->Tag != CALL_METHOD_T) {
                return;
        }
        bc_Method* m = bc_GetMethodByContext(cctx);
        bc_GenericType* arg = bc_AtVector(m->ReturnGType->TypeArgs, 0);
        //戻り値の型に互換性がない
        if (bc_DistanceGenericType(arg, bc_EvalILFactor(self->Value, env, cctx),
                                   cctx) < 0) {
                bc_Panic(BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T,
                         bc_Ref2Str(bc_GetTypeName(BC_MEMBER_TYPE(m))),
                         bc_Ref2Str(m->Name));
        }
}