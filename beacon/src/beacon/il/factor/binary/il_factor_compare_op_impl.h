#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct generic_type;
struct enviroment;
typedef struct il_factor_compare_op {
	struct il_factor_binary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_compare_op;

il_factor_compare_op* NewILCompareOp(operator_type type);

struct generic_type* EvalILCompareOp(il_factor_compare_op * self, struct enviroment * env, call_context* cctx);

void il_factor_compare_op_generate(il_factor_compare_op* self, struct enviroment* env, call_context* cctx);

void LoadILCompareOp(il_factor_compare_op* self, struct enviroment* env, call_context* cctx);

void il_factor_compare_op_delete(il_factor_compare_op* self);

char* il_factor_compare_op_tostr(il_factor_compare_op* self, struct enviroment* env);
#endif