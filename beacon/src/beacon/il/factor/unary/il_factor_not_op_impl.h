// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_not_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct bc_ILUnaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct bc_ILNotOp {
        struct bc_ILUnaryOp* Parent;
        bc_OperatorType Type;
        int OperatorIndex;
} bc_ILNotOp;

bc_ILNotOp* bc_NewILNotOp(bc_OperatorType type);

struct bc_GenericType* bc_EvalILNotOp(bc_ILNotOp* self,
                                      struct bc_Enviroment* env,
                                      bc_CallContext* cctx);

void bc_GenerateILNotOp(bc_ILNotOp* self, struct bc_Enviroment* env,
                        bc_CallContext* cctx);

void bc_LoadILNotOp(bc_ILNotOp* self, struct bc_Enviroment* env,
                    bc_CallContext* cctx);

void bc_DeleteILNotOp(bc_ILNotOp* self);

char* bc_ILNotOpToString(bc_ILNotOp* self, struct bc_Enviroment* env);
#endif