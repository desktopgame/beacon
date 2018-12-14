#include "il_factor_unary_op_impl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "unary/il_factor_childa_op_impl.h"
#include "unary/il_factor_negative_op_impl.h"
#include "unary/il_factor_not_op_impl.h"

bc_ILFactor* bc_WrapILUnaryOp(bc_ILUnaryOp* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_UNARY_OP_T);
        ret->Kind.UnaryOp = self;
        return ret;
}

bc_ILUnaryOp* bc_NewILUnaryOp(bc_OperatorType type) {
        bc_ILUnaryOp* ret = (bc_ILUnaryOp*)MEM_MALLOC(sizeof(bc_ILUnaryOp));
        ret->Type = type;
        ret->Arg = NULL;
        if (type == OPERATOR_NOT_T) ret->Kind.NotOp = NULL;
        if (type == OPERATOR_CHILDA_T) ret->Kind.ChildaOp = NULL;
        if (type == OPERATOR_NEGATIVE_T) ret->Kind.NegativeOp = NULL;
        return ret;
}

void bc_GenerateILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        switch (self->Type) {
                case OPERATOR_NOT_T:
                        bc_GenerateILNotOp(self->Kind.NotOp, env, cctx);
                        break;
                case OPERATOR_CHILDA_T:
                        bc_GenerateILChildaOp(self->Kind.ChildaOp, env, cctx);
                        break;
                case OPERATOR_NEGATIVE_T:
                        bc_GenerateILNegativeOp(self->Kind.NegativeOp, env,
                                                cctx);
                        break;
        }
}

void bc_LoadILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env,
                      bc_CallContext* cctx) {
        if (self->Type == OPERATOR_NOT_T && self->Kind.NotOp != NULL) return;
        if (self->Type == OPERATOR_CHILDA_T && self->Kind.ChildaOp != NULL)
                return;
        if (self->Type == OPERATOR_NEGATIVE_T && self->Kind.NegativeOp != NULL)
                return;
        bc_LoadILFactor(self->Arg, env, cctx);
        //カテゴリーわけ
        if (self->Type == OPERATOR_NOT_T) {
                self->Category = OPERATOR_CNOT_T;
                bc_ILNotOp* not = bc_NewILNotOp(self->Type);
                not->Parent = self;
                self->Kind.NotOp = not;
                bc_LoadILNotOp(not, env, cctx);
        } else if (self->Type == OPERATOR_NEGATIVE_T) {
                self->Category = OPERATOR_NEGATIVE_T;
                bc_ILNegativeOp* neg = bc_NewILNegativeOp(self->Type);
                neg->Parent = self;
                self->Kind.NegativeOp = neg;
                bc_LoadILNegativeOp(neg, env, cctx);
        } else if (self->Type == OPERATOR_CHILDA_T) {
                self->Category = OPERATOR_CCHILDA_T;
                bc_ILChildaOp* childa = bc_NewILChildaOp(self->Type);
                childa->Parent = self;
                self->Kind.ChildaOp = childa;
                bc_LoadILChildaOp(childa, env, cctx);
        } else {
                assert(false);
        }
}

bc_GenericType* bc_EvalILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env,
                                 bc_CallContext* cctx) {
        bc_LoadILUnaryOp(self, env, cctx);
        bc_GenericType* ret = NULL;
        switch (self->Type) {
                case OPERATOR_NOT_T:
                        ret = bc_EvalILNotOp(self->Kind.NotOp, env, cctx);
                        break;
                case OPERATOR_CHILDA_T:
                        ret = bc_EvalILChildaOp(self->Kind.ChildaOp, env, cctx);
                        break;
                case OPERATOR_NEGATIVE_T:
                        ret = bc_EvalILNegativeOp(self->Kind.NegativeOp, env,
                                                  cctx);
                        break;
        }
        return ret;
}

char* bc_ILUnaryOpToString(bc_ILUnaryOp* self, bc_Enviroment* env) {
        char* ret = NULL;
        switch (self->Type) {
                case OPERATOR_NOT_T:
                        ret = bc_ILNotOpToString(self->Kind.NotOp, env);
                        break;
                case OPERATOR_CHILDA_T:
                        ret = bc_ILChildaOpToString(self->Kind.ChildaOp, env);
                        break;
                case OPERATOR_NEGATIVE_T:
                        ret =
                            bc_ILNegativeOpToString(self->Kind.NegativeOp, env);
                        break;
        }
        return ret;
}

void bc_DeleteILUnaryOp(bc_ILUnaryOp* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteILFactor(self->Arg);
        switch (self->Type) {
                case OPERATOR_NOT_T:
                        bc_DeleteILNotOp(self->Kind.NotOp);
                        break;
                case OPERATOR_CHILDA_T:
                        bc_DeleteILChildaOp(self->Kind.ChildaOp);
                        break;
                case OPERATOR_NEGATIVE_T:
                        bc_DeleteILNegativeOp(self->Kind.NegativeOp);
                        break;
        }
        MEM_FREE(self);
}

char* bc_ILUnaryOpToStringSimple(bc_ILUnaryOp* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char* a = bc_ILFactorToString(self->Arg, env);
        bc_AppendfBuffer(sb, "%s", bc_OperatorToString(self->Type));
        bc_AppendsBuffer(sb, a);
        MEM_FREE(a);
        return bc_ReleaseBuffer(sb);
}

int bc_GetIndexILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        return bc_GetIndexILUnaryOp2(self->Arg, self->Type, env, cctx);
}

int bc_GetIndexILUnaryOp2(bc_ILFactor* receiver, bc_OperatorType otype,
                          bc_Enviroment* env, bc_CallContext* cctx) {
        bc_Vector* args = bc_NewVector();
        bc_GenericType* gtype = bc_EvalILFactor(receiver, env, cctx);
        if (gtype->VirtualTypeIndex != -1) {
                assert(false);
        }
        bc_Class* lclass = BC_TYPE2CLASS(bc_GENERIC2TYPE(gtype));
        int temp = 0;
#if defined(_MSC_VER)
        bc_GenericType* gargs =
            MEM_MALLOC(sizeof(bc_GenericType*) * args->Length);
#else
        bc_GenericType* gargs[args->Length];
#endif
        // bc_CevaluateArguments(args, gargs, env, cctx);
        bc_CreateOperatorVTClass(lclass);
        bc_ResolveOperatorOverload(lclass, otype, args->Length, gargs, cctx,
                                   &temp);
        // bc_GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
#if defined(_MSC_VER)
        MEM_FREE(gargs);
#endif
        return temp;
}

bc_GenericType* bc_ApplyILUnaryOp(bc_ILUnaryOp* self, bc_GenericType* gtype,
                                  bc_Enviroment* env, bc_CallContext* cctx) {
        bc_GenericType* lgtype = bc_EvalILFactor(self->Arg, env, cctx);
        bc_CallFrame* cfr = bc_PushCallFrame(cctx, lgtype, NULL, NULL);
        bc_GenericType* ret = bc_CapplyGenericType(gtype, cctx);
        bc_PopCallFrame(cctx);
        return ret;
}