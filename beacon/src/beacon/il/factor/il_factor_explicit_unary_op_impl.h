#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct il_factor;
struct enviroment;
struct generic_type;

typedef struct il_factor_explicit_unary_op {
	struct il_factor* receiver;
	operator_type type;
	int index;
} il_factor_explicit_unary_op;

struct il_factor* il_factor_wrap_explicit_unary_op(il_factor_explicit_unary_op* self);

il_factor_explicit_unary_op* il_factor_explicit_unary_op_new(operator_type type);

void il_factor_explicit_unary_op_dump(il_factor_explicit_unary_op* self, int depth);

void il_factor_explicit_unary_op_generate(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

void il_factor_explicit_unary_op_load(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

struct generic_type* il_factor_explicit_unary_op_eval(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

void il_factor_explicit_unary_op_delete(il_factor_explicit_unary_op* self);
#endif