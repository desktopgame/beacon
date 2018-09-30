#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_unary_op;
struct generic_type;
struct enviroment;

typedef struct il_factor_childa_op {
	struct il_factor_unary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_childa_op;

il_factor_childa_op* NewILChildaOp(operator_type type);

struct generic_type* EvalILChildaOp(il_factor_childa_op * self, struct enviroment * env, call_context* cctx);

void il_factor_childa_op_generate(il_factor_childa_op* self, struct enviroment* env, call_context* cctx);

void LoadILChildaOp(il_factor_childa_op* self, struct enviroment* env, call_context* cctx);

void DeleteILChildaOp(il_factor_childa_op* self);

char* ILChildaOpToString(il_factor_childa_op* self, struct enviroment* env);
#endif