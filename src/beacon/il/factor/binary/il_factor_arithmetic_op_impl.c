#include "il_factor_arithmetic_op_impl.h"
#include <assert.h>
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/generic_type.h"
#include "../../../env/namespace.h"
#include "../../../env/operator_overload.h"
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

bc_ILArithmeticOp* bc_NewILArithmeticOp(bc_OperatorType type) {
        bc_ILArithmeticOp* ret =
            (bc_ILArithmeticOp*)MEM_MALLOC(sizeof(bc_ILArithmeticOp));
        ret->Type = type;
        ret->Parent = NULL;
        ret->OperatorIndex = -1;
        return ret;
}

bc_GenericType* bc_EvalILArithmeticOp(bc_ILArithmeticOp* self,
                                      bc_Enviroment* env,
                                      bc_CallContext* cctx) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
        bc_GenericType* rgtype =
            bc_EvalILFactor(self->Parent->Right, env, cctx);
        assert(lgtype != NULL);
        assert(rgtype != NULL);
        bc_Type* cint = BC_TYPE_INT;
        bc_Type* cdouble = BC_TYPE_DOUBLE;
        if (bc_IsShortShortBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(BC_TYPE_SHORT);
        }
        if (bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(cint);
        }
        if (bc_IsLongLongBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(BC_TYPE_LONG);
        }
        if (bc_IsFloatFloatBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(BC_TYPE_FLOAT);
        }
        if (bc_IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
                return bc_TYPE2GENERIC(cdouble);
        }
        //プリミティブ型同士でないのに
        //演算子オーバーロードもない
        if (self->OperatorIndex == -1) {
                bc_Panic(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
                         bc_OperatorToString(self->Type));
                return NULL;
        }
        bc_OperatorOverload* operator_ov = bc_LookupOperatorOverload(
            BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
        return bc_ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env,
                                  cctx);
}

void bc_GenerateILArithmeticOp(bc_ILArithmeticOp* self, bc_Enviroment* env,
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

void bc_LoadILArithmeticOp(bc_ILArithmeticOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        if (!bc_IsShortShortBinaryOp(self->Parent, env, cctx) &&
            !bc_IsIntIntBinaryOp(self->Parent, env, cctx) &&
            !bc_IsLongLongBinaryOp(self->Parent, env, cctx) &&
            !bc_IsFloatFloatBinaryOp(self->Parent, env, cctx) &&
            !bc_IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
                self->OperatorIndex =
                    bc_GetIndexILBinaryOp(self->Parent, env, cctx);
        }
}

void bc_DeleteILArithmeticOp(bc_ILArithmeticOp* self) { MEM_FREE(self); }

char* bc_ILArithmeticOpToString(bc_ILArithmeticOp* self, bc_Enviroment* env) {
        return bc_ILBinaryOpToStringSimple(self->Parent, env);
}
// static
static bc_Opcode operator_to_sopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_ADD_T:
                        return OP_SADD;
                case OPERATOR_SUB_T:
                        return OP_SSUB;
                case OPERATOR_MUL_T:
                        return OP_SMUL;
                case OPERATOR_DIV_T:
                        return OP_SDIV;
                case OPERATOR_MOD_T:
                        return OP_SMOD;
        }
        assert(false);
}

static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_ADD_T:
                        return OP_IADD;
                case OPERATOR_SUB_T:
                        return OP_ISUB;
                case OPERATOR_MUL_T:
                        return OP_IMUL;
                case OPERATOR_DIV_T:
                        return OP_IDIV;
                case OPERATOR_MOD_T:
                        return OP_IMOD;
        }
        assert(false);
}

static bc_Opcode operator_to_lopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_ADD_T:
                        return OP_LADD;
                case OPERATOR_SUB_T:
                        return OP_LSUB;
                case OPERATOR_MUL_T:
                        return OP_LMUL;
                case OPERATOR_DIV_T:
                        return OP_LDIV;
                case OPERATOR_MOD_T:
                        return OP_LMOD;
        }
        assert(false);
}

static bc_Opcode operator_to_fopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_ADD_T:
                        return OP_FADD;
                case OPERATOR_SUB_T:
                        return OP_FSUB;
                case OPERATOR_MUL_T:
                        return OP_FMUL;
                case OPERATOR_DIV_T:
                        return OP_FDIV;
                case OPERATOR_MOD_T:
                        return OP_FMOD;
        }
        assert(false);
}

static bc_Opcode operator_to_dopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_ADD_T:
                        return OP_DADD;
                case OPERATOR_SUB_T:
                        return OP_DSUB;
                case OPERATOR_MUL_T:
                        return OP_DMUL;
                case OPERATOR_DIV_T:
                        return OP_DDIV;
                case OPERATOR_MOD_T:
                        return OP_DMOD;
        }
        assert(false);
}