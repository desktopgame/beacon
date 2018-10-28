#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILUnaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILFactor_negative_op {
	struct ILUnaryOp* parent;
	OperatorType type;
	int operator_index;
} ILFactor_negative_op;

#define ILFactor_negative_op_new(type) (MallocILNegativeOp(type, __FILE__, __LINE__))
ILFactor_negative_op* MallocILNegativeOp(OperatorType type, const char* filename, int lineno);

struct GenericType* EvalILNegativeOp(ILFactor_negative_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNegativeOp(ILFactor_negative_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILNegativeOp(ILFactor_negative_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNegativeOp(ILFactor_negative_op* self);

char* ILNegativeOpToString(ILFactor_negative_op* self, struct Enviroment* env);
#endif