#include "il_factor_shift_op_impl.h"
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
static bc_Opcode operator_to_dopcode(bc_OperatorType type);

bc_ILShiftOp* bc_NewILShiftOp(bc_OperatorType type) {
        bc_ILShiftOp* ret = (bc_ILShiftOp*)MEM_MALLOC(sizeof(bc_ILShiftOp));
        ret->Parent = NULL;
        ret->Type = type;
        ret->OperatorIndex = -1;
        return ret;
}

bc_GenericType* bc_EvalILShiftOp(bc_ILShiftOp* self, bc_Enviroment* env,
                                 bc_CallContext* cctx) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
        bc_GenericType* rgtype =
            bc_EvalILFactor(self->Parent->Right, env, cctx);
        assert(lgtype != NULL);
        assert(rgtype != NULL);
        bc_Type* cint = BC_TYPE_INT;
        bc_Type* cdouble = BC_TYPE_DOUBLE;
        if (bc_GENERIC2TYPE(lgtype) == cint &&
            bc_GENERIC2TYPE(rgtype) == cint) {
                return bc_TYPE2GENERIC(cint);
        }
        if (bc_GENERIC2TYPE(lgtype) == BC_TYPE_SHORT &&
            bc_GENERIC2TYPE(rgtype) == BC_TYPE_SHORT) {
                return bc_TYPE2GENERIC(BC_TYPE_SHORT);
        }
        if (bc_GENERIC2TYPE(lgtype) == BC_TYPE_LONG &&
            bc_GENERIC2TYPE(rgtype) == BC_TYPE_LONG) {
                return bc_TYPE2GENERIC(BC_TYPE_LONG);
        }
        if (self->OperatorIndex == -1) {
                bc_Panic(BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
                         bc_OperatorToString(self->Type));
                return NULL;
        }
        bc_OperatorOverload* operator_ov = bc_LookupOperatorOverload(
            BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
        return bc_ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env,
                                  cctx);
}

void bc_GenerateILShiftOp(bc_ILShiftOp* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
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
                } else {
                        bc_Panic(BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
                                 bc_OperatorToString(self->Type));
                }
        } else {
                bc_GenerateILFactor(self->Parent->Right, env, cctx);
                bc_GenerateILFactor(self->Parent->Left, env, cctx);
                bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
                bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
        }
}

void bc_LoadILShiftOp(bc_ILShiftOp* self, bc_Enviroment* env,
                      bc_CallContext* cctx) {
        if (!bc_IsShortShortBinaryOp(self->Parent, env, cctx) &&
            !bc_IsIntIntBinaryOp(self->Parent, env, cctx) &&
            !bc_IsLongLongBinaryOp(self->Parent, env, cctx)) {
                self->OperatorIndex =
                    bc_GetIndexILBinaryOp(self->Parent, env, cctx);
        }
}

void bc_DeleteILShiftOp(bc_ILShiftOp* self) { MEM_FREE(self); }

char* bc_ILShiftOpToString(bc_ILShiftOp* self, bc_Enviroment* env) {
        return bc_ILBinaryOpToStringSimple(self->Parent, env);
}
// static
static bc_Opcode operator_to_sopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_LSHIFT_T:
                        return OP_SLSH;
                case OPERATOR_RSHIFT_T:
                        return OP_SRSH;
        }
        assert(false);
}

static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_LSHIFT_T:
                        return OP_ILSH;
                case OPERATOR_RSHIFT_T:
                        return OP_IRSH;
        }
        assert(false);
}

static bc_Opcode operator_to_lopcode(bc_OperatorType type) {
        switch (type) {
                case OPERATOR_LSHIFT_T:
                        return OP_LLSH;
                case OPERATOR_RSHIFT_T:
                        return OP_LRSH;
        }
        assert(false);
}

static bc_Opcode operator_to_dopcode(bc_OperatorType type) { assert(false); }