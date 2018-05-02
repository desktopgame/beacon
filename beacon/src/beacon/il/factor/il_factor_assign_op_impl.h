#ifndef BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#define BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#include "../il_factor_interface.h"
struct generic_type;
typedef struct il_factor_assign_op {
	il_factor* left;
	il_factor* right;
} il_factor_assign_op;

il_factor* il_factor_wrap_assign(il_factor_assign_op* self);

il_factor_assign_op* il_factor_assign_op_new();

void il_factor_assign_op_dump(il_factor_assign_op* self, int depth);

void il_factor_assign_op_load(il_factor_assign_op* self, enviroment* env, il_context* ilctx);

void il_factor_assign_op_generate(il_factor_assign_op* self, enviroment* env, il_context* ilctx);

struct generic_type* il_factor_assign_op_eval(il_factor_assign_op* self, enviroment* env, il_context* ilctx);

void il_factor_assign_op_delete(il_factor_assign_op* self);
#endif