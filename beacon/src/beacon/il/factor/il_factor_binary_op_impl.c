#include "il_factor_binary_op_impl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/field.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../il_factor_impl.h"
#include "binary/il_factor_arithmetic_op_impl.h"
#include "binary/il_factor_compare_op_impl.h"
#include "il_factor_variable_impl.h"
//#include "binary/ILAssignOp_impl.h"
#include "binary/il_factor_excor_op_impl.h"
#include "binary/il_factor_logic_op_impl.h"
#include "binary/il_factor_shift_op_impl.h"

static bool type_test(bc_ILBinaryOp* self, bc_Enviroment* env,
                      bc_CallContext* cctx, bc_Type* t);

bc_ILFactor* bc_WrapILBinaryOp(bc_ILBinaryOp* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_BINARY_OP_T);
        ret->Kind.BinaryOp = self;
        return ret;
}

bc_ILBinaryOp* bc_NewILBinaryOp(bc_OperatorType type) {
        bc_ILBinaryOp* ret = (bc_ILBinaryOp*)MEM_MALLOC(sizeof(bc_ILBinaryOp));
        ret->Type = type;
        ret->Left = NULL;
        ret->Right = NULL;
        ret->IsLoaded = false;
        return ret;
}

void bc_GenerateILBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        switch (self->Category) {
                case OPERATOR_CARITHMERIC_T:
                        bc_GenerateILArithmeticOp(self->Kind.ArithmeticOp, env,
                                                  cctx);
                        break;
                case OPERATOR_CCOMPARE_T:
                        bc_GenerateILCompareOp(self->Kind.CompareOp, env, cctx);
                        break;
                case OPERATOR_CLOGIC_T:
                        bc_GenerateILLogicOp(self->Kind.LogicOp, env, cctx);
                        break;
                case OPERATOR_CSHIFT_T:
                        bc_GenerateILShiftOp(self->Kind.ShiftOp, env, cctx);
                        break;
                case OPERATOR_CEXCOR_T:
                        bc_GenerateILExcorOp(self->Kind.ExcorOp, env, cctx);
                        break;
        }
}

void bc_LoadILBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        if (self->IsLoaded) {
                return;
        }
        self->IsLoaded = true;
        bc_LoadILFactor(self->Left, env, cctx);
        BC_ERROR();
        bc_LoadILFactor(self->Right, env, cctx);
        BC_ERROR();
        //カテゴリーわけ
        if (bc_IsArithmeticOperator(self->Type)) {
                self->Category = OPERATOR_CARITHMERIC_T;
                bc_ILArithmeticOp* arith = bc_NewILArithmeticOp(self->Type);
                arith->Parent = self;
                self->Kind.ArithmeticOp = arith;
                bc_LoadILArithmeticOp(arith, env, cctx);
        } else if (bc_IsCompareOperator(self->Type)) {
                self->Category = OPERATOR_CCOMPARE_T;
                bc_ILCompareOp* comp = bc_NewILCompareOp(self->Type);
                comp->Parent = self;
                self->Kind.CompareOp = comp;
                bc_LoadILCompareOp(comp, env, cctx);
        } else if (bc_IsBitOperator(self->Type) ||
                   bc_IsLogicOperator(self->Type)) {
                self->Category = OPERATOR_CLOGIC_T;
                bc_ILLogicOp* logic = bc_NewILLogicOp(self->Type);
                logic->Parent = self;
                self->Kind.LogicOp = logic;
                bc_LoadILLogicOp(logic, env, cctx);
        } else if (bc_IsShiftOperator(self->Type)) {
                self->Category = OPERATOR_CSHIFT_T;
                bc_ILShiftOp* shift = bc_NewILShiftOp(self->Type);
                shift->Parent = self;
                self->Kind.ShiftOp = shift;
                bc_LoadILShiftOp(shift, env, cctx);
        } else if (self->Type == OPERATOR_EXCOR_T) {
                self->Category = OPERATOR_CEXCOR_T;
                bc_ILExcorOp* excor = bc_NewILExcorOp(self->Type);
                excor->Parent = self;
                self->Kind.ExcorOp = excor;
                bc_LoadILExcorOp(excor, env, cctx);
        } else {
                assert(false);
        }
}

bc_GenericType* bc_EvalILBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                                  bc_CallContext* cctx) {
        bc_LoadILBinaryOp(self, env, cctx);
        bc_GenericType* ret = NULL;
        switch (self->Category) {
                case OPERATOR_CARITHMERIC_T:
                        ret = bc_EvalILArithmeticOp(self->Kind.ArithmeticOp,
                                                    env, cctx);
                        break;
                case OPERATOR_CCOMPARE_T:
                        ret =
                            bc_EvalILCompareOp(self->Kind.CompareOp, env, cctx);
                        break;
                case OPERATOR_CLOGIC_T:
                        ret = bc_EvalILLogicOp(self->Kind.LogicOp, env, cctx);
                        break;
                case OPERATOR_CSHIFT_T:
                        ret = bc_EvalILShiftOp(self->Kind.ShiftOp, env, cctx);
                        break;
                case OPERATOR_CEXCOR_T:
                        ret = bc_EvalILExcorOp(self->Kind.ExcorOp, env, cctx);
                        break;
        }
        //	assert(ret != NULL);
        return ret;
}

char* bc_ILBinaryOpToString(bc_ILBinaryOp* self, bc_Enviroment* env) {
        char* ret = NULL;
        switch (self->Category) {
                case OPERATOR_CARITHMERIC_T:
                        ret = bc_ILArithmeticOpToString(self->Kind.ArithmeticOp,
                                                        env);
                        break;
                case OPERATOR_CLOGIC_T:
                        ret = bc_ILLogicOpToString(self->Kind.LogicOp, env);
                        break;
                case OPERATOR_CCOMPARE_T:
                        ret = bc_ILCompareOpToString(self->Kind.CompareOp, env);
                        break;
                case OPERATOR_CSHIFT_T:
                        ret = bc_ILShiftOpToString(self->Kind.ShiftOp, env);
                        break;
                case OPERATOR_CEXCOR_T:
                        ret = bc_ILExcorOpToString(self->Kind.ExcorOp, env);
                        break;
        }
        assert(ret != NULL);
        return ret;
}

void bc_DeleteILBinaryOp(bc_ILBinaryOp* self) {
        switch (self->Category) {
                case OPERATOR_CARITHMERIC_T:
                        bc_DeleteILArithmeticOp(self->Kind.ArithmeticOp);
                        break;
                case OPERATOR_CLOGIC_T:
                        bc_DeleteILLogicOp(self->Kind.LogicOp);
                        break;
                case OPERATOR_CCOMPARE_T:
                        bc_DeleteILCompareOp(self->Kind.CompareOp);
                        break;
                case OPERATOR_CSHIFT_T:
                        bc_DeleteILShiftOp(self->Kind.ShiftOp);
                        break;
                case OPERATOR_CEXCOR_T:
                        bc_DeleteILExcorOp(self->Kind.ExcorOp);
                        break;
        }
        bc_DeleteILFactor(self->Left);
        bc_DeleteILFactor(self->Right);
        MEM_FREE(self);
}

char* bc_ILBinaryOpToStringSimple(bc_ILBinaryOp* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char* a = bc_ILFactorToString(self->Left, env);
        char* b = bc_ILFactorToString(self->Right, env);
        bc_AppendsBuffer(sb, a);
        bc_AppendfBuffer(sb, " %s ", bc_OperatorToString(self->Type));
        bc_AppendsBuffer(sb, b);
        MEM_FREE(a);
        MEM_FREE(b);
        return bc_ReleaseBuffer(sb);
}

bool bc_IsIntIntBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        return type_test(self, env, cctx, BC_TYPE_INT);
}

bool bc_IsDoubleDoubleBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        return type_test(self, env, cctx, BC_TYPE_DOUBLE);
}

bool bc_IsBoolBoolBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        return type_test(self, env, cctx, BC_TYPE_BOOL);
}

bool bc_IsCharCharBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        return type_test(self, env, cctx, BC_TYPE_CHAR);
}

int bc_GetIndexILBinaryOp(bc_ILBinaryOp* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        if (bc_IsIntIntBinaryOp(self, env, cctx) ||
            bc_IsDoubleDoubleBinaryOp(self, env, cctx)) {
                return -1;
        }
        return bc_GetIndexILBinaryOp2(self->Left, self->Right, self->Type, env,
                                      cctx);
}

int bc_GetIndexILBinaryOp2(bc_ILFactor* receiver, bc_ILFactor* arg,
                           bc_OperatorType otype, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        bc_Vector* args = bc_NewVector();
        bc_GenericType* lgtype = bc_EvalILFactor(receiver, env, cctx);
        bc_GenericType* rgtype = bc_EvalILFactor(arg, env, cctx);

        bc_PushCallFrame(cctx, lgtype, args, NULL);
        // PushVector(args, lgtype);
        bc_PushVector(args, rgtype);
        bc_Type* lctype = bc_GENERIC2TYPE(lgtype);
        assert(lctype->Tag == TYPE_CLASS_T);
        bc_Class* lclass = BC_TYPE2CLASS(lctype);
        int temp = 0;
        bc_GenericType* gargs[args->Length];
        gargs[0] = rgtype;
        //        bc_CevaluateArguments(args, gargs, env, cctx);
        bc_CreateOperatorVTClass(lclass);
        bc_FindOperatorOverload(lclass->OVT->Operators, otype, args->Length,
                                gargs, MATCH_PUBLIC_ONLY, cctx, &temp);
        // bc_GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
        bc_PopCallFrame(cctx);
        return temp;
}

bc_GenericType* bc_ApplyILBinaryOp(bc_ILBinaryOp* self, bc_GenericType* gtype,
                                   bc_Enviroment* env, bc_CallContext* cctx) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Left, env, cctx);
        bc_CallFrame* cfr = bc_PushCallFrame(cctx, lgtype, NULL, NULL);
        bc_GenericType* ret = bc_CapplyGenericType(gtype, cctx);
        bc_PopCallFrame(cctx);
        return ret;
}

// private
static bool type_test(bc_ILBinaryOp* self, bc_Enviroment* env,
                      bc_CallContext* cctx, bc_Type* t) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Left, env, cctx);
        bc_GenericType* rgtype = bc_EvalILFactor(self->Right, env, cctx);
        return bc_GENERIC2TYPE(lgtype) == t && bc_GENERIC2TYPE(rgtype) == t;
}