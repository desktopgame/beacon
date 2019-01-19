// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_explicit_unary_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct bc_ILFactor;
struct bc_Enviroment;
struct bc_GenericType;

typedef struct bc_ILExplicitUnaryOp {
        struct bc_ILFactor* Receiver;
        bc_OperatorType Type;
        int Index;
} bc_ILExplicitUnaryOp;

struct bc_ILFactor* bc_WrapILExplicitUnaryOp(bc_ILExplicitUnaryOp* self);

bc_ILExplicitUnaryOp* bc_NewILExplicitUnaryOp(bc_OperatorType type);

void bc_GenerateILExplicitUnaryOp(bc_ILExplicitUnaryOp* self,
                                  struct bc_Enviroment* env,
                                  bc_CallContext* cctx);

void bc_LoadILExplicitUnaryOp(bc_ILExplicitUnaryOp* self,
                              struct bc_Enviroment* env, bc_CallContext* cctx);

struct bc_GenericType* bc_EvalILExplicitUnaryOp(bc_ILExplicitUnaryOp* self,
                                                struct bc_Enviroment* env,
                                                bc_CallContext* cctx);

void bc_DeleteILExplicitUnaryOp(bc_ILExplicitUnaryOp* self);
#endif