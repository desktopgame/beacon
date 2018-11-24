#include "il_factor_excor_op_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/generic_type.h"
#include "../../../env/namespace.h"
#include "../../../env/operator_overload.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"

bc_ILExcorOp* bc_NewILExcorOp(bc_OperatorType type) {
        bc_ILExcorOp* ret = (bc_ILExcorOp*)MEM_MALLOC(sizeof(bc_ILExcorOp));
        ret->Type = type;
        ret->Parent = NULL;
        ret->OperatorIndex = -1;
        return ret;
}

bc_GenericType* bc_EvalILExcorOp(bc_ILExcorOp* self, bc_Enviroment* env,
                                 bc_CallContext* cctx) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
        bc_GenericType* rgtype =
            bc_EvalILFactor(self->Parent->Right, env, cctx);
        assert(lgtype != NULL);
        assert(rgtype != NULL);
        if (bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(BC_TYPE_INT);
        }
        if (bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(BC_TYPE_BOOL);
        }
        //プリミティブ型同士でないのに
        //演算子オーバーロードもない
        if (self->OperatorIndex == -1) {
                bc_Panic(BCERROR_UNDEFINED_EXCOR_OPERATOR_T,
                         bc_OperatorToString(self->Type));
                return NULL;
        }
        bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(
            BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
        return bc_ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env,
                                  cctx);
}

void bc_GenerateILExcorOp(bc_ILExcorOp* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        //演算子オーバーロードが見つからない
        if (self->OperatorIndex == -1) {
                bc_GenerateILFactor(self->Parent->Right, env, cctx);
                bc_GenerateILFactor(self->Parent->Left, env, cctx);
                if (bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_IEXCOR);
                } else if (bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_BEXCOR);
                } else {
                        assert(false);
                }
        } else {
                bc_GenerateILFactor(self->Parent->Right, env, cctx);
                bc_GenerateILFactor(self->Parent->Left, env, cctx);
                bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
                bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
        }
}

void bc_LoadILExcorOp(bc_ILExcorOp* self, bc_Enviroment* env,
                      bc_CallContext* cctx) {
        if (!bc_IsIntIntBinaryOp(self->Parent, env, cctx) &&
            !bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
                self->OperatorIndex =
                    bc_GetIndexILBinaryOp(self->Parent, env, cctx);
        }
}

void bc_DeleteILExcorOp(bc_ILExcorOp* self) { MEM_FREE(self); }

char* bc_ILExcorOpToString(bc_ILExcorOp* self, bc_Enviroment* env) {
        return bc_ILBinaryOpToStringSimple(self->Parent, env);
}