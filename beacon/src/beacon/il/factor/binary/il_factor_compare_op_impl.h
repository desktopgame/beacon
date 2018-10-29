#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct GenericType;
struct Enviroment;
typedef struct ILCompareOp {
	struct ILBinaryOp* parent;
	OperatorType type;
	int operator_index;
} ILCompareOp;

ILCompareOp* NewILCompareOp(OperatorType type);

struct GenericType* EvalILCompareOp(ILCompareOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILCompareOp(ILCompareOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILCompareOp(ILCompareOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILCompareOp(ILCompareOp* self);

char* ILCompareOpToString(ILCompareOp* self, struct Enviroment* env);
#endif