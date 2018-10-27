#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct GenericType;
struct Enviroment;
typedef struct ILFactor_compare_op {
	struct ILBinaryOp* parent;
	OperatorType type;
	int operator_index;
} ILFactor_compare_op;

ILFactor_compare_op* NewILCompareOp(OperatorType type);

struct GenericType* EvalILCompareOp(ILFactor_compare_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILCompareOp(ILFactor_compare_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILCompareOp(ILFactor_compare_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILCompareOp(ILFactor_compare_op* self);

char* ILCompareOpToString(ILFactor_compare_op* self, struct Enviroment* env);
#endif