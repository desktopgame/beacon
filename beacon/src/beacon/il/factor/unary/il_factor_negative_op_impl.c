#include "il_factor_negative_op_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/generic_type.h"
#include "../../../env/namespace.h"
#include "../../../env/operator_overload.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../il_factor_unary_op_impl.h"

bc_ILNegativeOp* bc_MallocILNegativeOp(bc_OperatorType type,
                                       const char* filename, int lineno) {
        bc_ILNegativeOp* ret = (bc_ILNegativeOp*)bc_MXMalloc(
            sizeof(bc_ILNegativeOp), filename, lineno);
        ret->Type = type;
        ret->Parent = NULL;
        ret->OperatorIndex = -1;
        return ret;
}

bc_GenericType* bc_EvalILNegativeOp(bc_ILNegativeOp* self, bc_Enviroment* env,
                                    bc_CallContext* cctx) {
        return bc_EvalILFactor(self->Parent->Arg, env, cctx);
}

void bc_GenerateILNegativeOp(bc_ILNegativeOp* self, bc_Enviroment* env,
                             bc_CallContext* cctx) {
        bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
        if (self->OperatorIndex == -1) {
                bc_GenerateILFactor(self->Parent->Arg, env, cctx);
                if (bc_GENERIC2TYPE(gt) == BC_TYPE_INT) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_INEG);
                } else if (bc_GENERIC2TYPE(gt) == BC_TYPE_DOUBLE) {
                        bc_AddOpcodeBuf(env->Bytecode, OP_DNEG);
                } else {
                        assert(false);
                }
        } else {
                bc_GenerateILFactor(self->Parent->Arg, env, cctx);
                bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
                bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
        }
}

void bc_LoadILNegativeOp(bc_ILNegativeOp* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
        if (bc_GENERIC2TYPE(gt) != BC_TYPE_INT &&
            bc_GENERIC2TYPE(gt) != BC_TYPE_DOUBLE) {
                self->OperatorIndex =
                    bc_GetIndexILUnaryOp(self->Parent, env, cctx);
        }
}

void bc_DeleteILNegativeOp(bc_ILNegativeOp* self) { MEM_FREE(self); }

char* bc_ILNegativeOpToString(bc_ILNegativeOp* self, bc_Enviroment* env) {
        return bc_ILUnaryOpToStringSimple(self->Parent, env);
}