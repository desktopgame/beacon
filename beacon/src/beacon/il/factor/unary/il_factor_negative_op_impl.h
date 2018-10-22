#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_unary_op;
struct generic_type;
struct Enviroment;

typedef struct il_factor_negative_op {
	struct il_factor_unary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_negative_op;

#define il_factor_negative_op_new(type) (MallocILNegativeOp(type, __FILE__, __LINE__))
il_factor_negative_op* MallocILNegativeOp(OperatorType type, const char* filename, int lineno);

struct generic_type* EvalILNegativeOp(il_factor_negative_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNegativeOp(il_factor_negative_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILNegativeOp(il_factor_negative_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNegativeOp(il_factor_negative_op* self);

char* ILNegativeOpToString(il_factor_negative_op* self, struct Enviroment* env);
#endif