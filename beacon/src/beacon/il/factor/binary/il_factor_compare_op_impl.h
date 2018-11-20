//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_compare_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct bc_GenericType;
struct bc_Enviroment;
typedef struct ILCompareOp {
	struct ILBinaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} ILCompareOp;

ILCompareOp* NewILCompareOp(bc_OperatorType type);

struct bc_GenericType* EvalILCompareOp(ILCompareOp * self, struct bc_Enviroment * env, CallContext* cctx);

void GenerateILCompareOp(ILCompareOp* self, struct bc_Enviroment* env, CallContext* cctx);

void LoadILCompareOp(ILCompareOp* self, struct bc_Enviroment* env, CallContext* cctx);

void DeleteILCompareOp(ILCompareOp* self);

char* ILCompareOpToString(ILCompareOp* self, struct bc_Enviroment* env);
#endif