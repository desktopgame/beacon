#include "il_factor_compare_op_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/generic_type.h"
#include "../../../env/namespace.h"
#include "../../../env/type_interface.h"
#include "../../../util/mem.h"
#include "../../../util/string_buffer.h"
#include "../../../util/text.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"

static bc_Opcode operator_to_sopcode(bc_OperatorType type);
static bc_Opcode operator_to_iopcode(bc_OperatorType type);
static bc_Opcode operator_to_lopcode(bc_OperatorType type);
static bc_Opcode operator_to_fopcode(bc_OperatorType type);
static bc_Opcode operator_to_dopcode(bc_OperatorType type);
static bc_Opcode operator_to_copcode(bc_OperatorType type);

bc_ILCompareOp* bc_NewILCompareOp(bc_OperatorType type) {
        bc_ILCompareOp* ret =
            (bc_ILCompareOp*)MEM_MALLOC(sizeof(bc_ILCompareOp));
        ret->Type = type;
        ret->Parent = NULL;
        ret->OperatorIndex = -1;
        return ret;
}

bc_GenericType* bc_EvalILCompareOp(bc_ILCompareOp* self, bc_Enviroment* env,
                                   bc_CallContext* cctx) {
        bc_GenericType* ret = bc_TYPE2GENERIC(BC_TYPE_BOOL);
        assert(ret != NULL);
        return ret;
}

void bc_GenerateILCompareOp(bc_ILCompareOp* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        //演算子オーバーロードが見つからない
        if (self->OperatorIndex == -1) {
                bc_GenerateILFactor(self->Parent->Right, env, cctx);
                bc_GenerateILFactor(self->Parent->Left, env, cctx);
                if (bc_IsShortShortBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_sopcode(self->Type));
                } else if (bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_iopcode(self->Type));
                } else if (bc_IsLongLongBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_lopcode(self->Type));
                } else if (bc_IsFloatFloatBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_fopcode(self->Type));
                } else if (bc_IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_dopcode(self->Type));
                } else if (bc_IsCharCharBinaryOp(self->Parent, env, cctx)) {
                        bc_AddOpcodeBuf(
                            env->Bytecode,
                            (bc_VectorItem)operator_to_copcode(self->Type));
                } else {
                        bc_Panic(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
                                 bc_OperatorToString(self->Type));
                        //			assert(false);
                }
        } else {
                bc_GenerateILFactor(self->Parent->Right, env, cctx);
                bc_GenerateILFactor(self->Parent->Left, env, cctx);
                bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
                bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
        }
}

void bc_LoadILCompareOp(bc_ILCompareOp* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        if (!bc_IsShortShortBinaryOp(self->Parent, env, cctx) &&
            !bc_IsIntIntBinaryOp(self->Parent, env, cctx) &&
            !bc_IsLongLongBinaryOp(self->Parent, env, cctx) &&
            !bc_IsFloatFloatBinaryOp(self->Parent, env, cctx) &&
            !bc_IsDoubleDoubleBinaryOp(self->Parent, env, cctx) &&
            !bc_IsCharCharBinaryOp(self->Parent, env, cctx)) {
                self->OperatorIndex =
                    bc_GetIndexILBinaryOp(self->Parent, env, cctx);
        }
}

void bc_DeleteILCompareOp(bc_ILCompareOp* self) { MEM_FREE(self); }

char* bc_ILCompareOpToString(bc_ILCompareOp* self, bc_Enviroment* env) {
        return bc_ILBinaryOpToStringSimple(self->Parent, env);
}
// static
static bc_Opcode operator_to_sopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_SGT;
                case OPERATOR_GE_T:
                        return OP_SGE;
                case OPERATOR_LT_T:
                        return OP_SLT;
                case OPERATOR_LE_T:
                        return OP_SLE;
                case OPERATOR_EQ_T:
                        return OP_SEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_SNOTEQ;
        }
        assert(false);
}

static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_IGT;
                case OPERATOR_GE_T:
                        return OP_IGE;
                case OPERATOR_LT_T:
                        return OP_ILT;
                case OPERATOR_LE_T:
                        return OP_ILE;
                case OPERATOR_EQ_T:
                        return OP_IEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_INOTEQ;
        }
        assert(false);
}

static bc_Opcode operator_to_lopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_LGT;
                case OPERATOR_GE_T:
                        return OP_LGE;
                case OPERATOR_LT_T:
                        return OP_LLT;
                case OPERATOR_LE_T:
                        return OP_LLE;
                case OPERATOR_EQ_T:
                        return OP_LEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_LNOTEQ;
        }
        assert(false);
}

static bc_Opcode operator_to_fopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_FGT;
                case OPERATOR_GE_T:
                        return OP_FGE;
                case OPERATOR_LT_T:
                        return OP_FLT;
                case OPERATOR_LE_T:
                        return OP_FLE;
                case OPERATOR_EQ_T:
                        return OP_FEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_FNOTEQ;
        }
        assert(false);
}

static bc_Opcode operator_to_dopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_DGT;
                case OPERATOR_GE_T:
                        return OP_DGE;
                case OPERATOR_LT_T:
                        return OP_DLT;
                case OPERATOR_LE_T:
                        return OP_DLE;
                case OPERATOR_EQ_T:
                        return OP_DEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_DNOTEQ;
        }
        assert(false);
}

static bc_Opcode operator_to_copcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_GT_T:
                        return OP_CGT;
                case OPERATOR_GE_T:
                        return OP_CGE;
                case OPERATOR_LT_T:
                        return OP_CLT;
                case OPERATOR_LE_T:
                        return OP_CLE;
                case OPERATOR_EQ_T:
                        return OP_CEQ;
                case OPERATOR_NOT_EQ_T:
                        return OP_CNOTEQ;
        }
        assert(false);
}