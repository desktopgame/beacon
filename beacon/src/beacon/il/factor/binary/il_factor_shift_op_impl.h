#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct generic_type;
struct enviroment;
struct il_factor_binary_op;
typedef struct il_factor_shift_op {
	struct il_factor_binary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_shift_op;

il_factor_shift_op* il_factor_shift_op_new(operator_type type);

void il_factor_shift_op_dump(il_factor_shift_op* self, int depth);

struct generic_type* il_factor_shift_op_eval(il_factor_shift_op * self, struct enviroment * env, call_context* cctx);

void il_factor_shift_op_generate(il_factor_shift_op* self, struct enviroment* env, call_context* cctx);

void il_factor_shift_op_load(il_factor_shift_op* self, struct enviroment* env, call_context* cctx);

void il_factor_shift_op_delete(il_factor_shift_op* self);

char* il_factor_shift_op_tostr(il_factor_shift_op* self, struct enviroment* env);
#endif