// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_excor_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct bc_ILBinaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct bc_ILExcorOp {
        struct bc_ILBinaryOp* Parent;
        bc_OperatorType Type;
        int OperatorIndex;
} bc_ILExcorOp;

bc_ILExcorOp* bc_NewILExcorOp(bc_OperatorType type);

struct bc_GenericType* bc_EvalILExcorOp(bc_ILExcorOp* self,
                                        struct bc_Enviroment* env,
                                        bc_CallContext* cctx);

void bc_GenerateILExcorOp(bc_ILExcorOp* self, struct bc_Enviroment* env,
                          bc_CallContext* cctx);

void bc_LoadILExcorOp(bc_ILExcorOp* self, struct bc_Enviroment* env,
                      bc_CallContext* cctx);

void bc_DeleteILExcorOp(bc_ILExcorOp* self);

char* bc_ILExcorOpToString(bc_ILExcorOp* self, struct bc_Enviroment* env);
#endif