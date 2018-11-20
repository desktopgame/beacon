//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_childa_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILUnaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct ILChildaOp {
	struct ILUnaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} ILChildaOp;

ILChildaOp* NewILChildaOp(bc_OperatorType type);

struct bc_GenericType* EvalILChildaOp(ILChildaOp * self, struct bc_Enviroment * env, CallContext* cctx);

void GenerateILChildaOp(ILChildaOp* self, struct bc_Enviroment* env, CallContext* cctx);

void LoadILChildaOp(ILChildaOp* self, struct bc_Enviroment* env, CallContext* cctx);

void DeleteILChildaOp(ILChildaOp* self);

char* ILChildaOpToString(ILChildaOp* self, struct bc_Enviroment* env);
#endif