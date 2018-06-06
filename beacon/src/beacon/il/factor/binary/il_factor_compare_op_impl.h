#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
struct il_factor_binary_op;
typedef struct il_factor_compare_op {
	struct il_factor_binary_op* parent;
	operator_type type;
} il_factor_compare_op;

il_factor_compare_op* il_factor_compare_op_new(operator_type type);

void il_factor_compare_op_delete(il_factor_compare_op* self);
#endif