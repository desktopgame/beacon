//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_not_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct bc_ILUnaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct ILNotOp {
	struct bc_ILUnaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} ILNotOp;

ILNotOp* NewILNotOp(bc_OperatorType type);

struct bc_GenericType* EvalILNotOp(ILNotOp * self, struct bc_Enviroment * env, bc_CallContext* cctx);

void GenerateILNotOp(ILNotOp* self, struct bc_Enviroment* env, bc_CallContext* cctx);

void LoadILNotOp(ILNotOp* self, struct bc_Enviroment* env, bc_CallContext* cctx);

void DeleteILNotOp(ILNotOp* self);

char* ILNotOpToString(ILNotOp* self, struct bc_Enviroment* env);
#endif