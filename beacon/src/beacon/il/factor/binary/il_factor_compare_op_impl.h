#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct generic_type;
struct Enviroment;
typedef struct il_factor_compare_op {
	struct il_factor_binary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_compare_op;

il_factor_compare_op* NewILCompareOp(OperatorType type);

struct generic_type* EvalILCompareOp(il_factor_compare_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILCompareOp(il_factor_compare_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILCompareOp(il_factor_compare_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILCompareOp(il_factor_compare_op* self);

char* ILCompareOpToString(il_factor_compare_op* self, struct Enviroment* env);
#endif