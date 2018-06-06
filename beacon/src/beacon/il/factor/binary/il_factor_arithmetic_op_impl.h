#ifndef BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#define BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#include "../../../ast/operator_type.h"
struct il_factor_binary_op;
typedef struct il_factor_arithmeric_op {
	struct il_factor_binary_op* parent;
	operator_type type;
} il_factor_arithmeric_op;

il_factor_arithmeric_op* il_factor_arithmeric_op_new(operator_type type);

void il_factor_arithmeric_op_delete(il_factor_arithmeric_op* self);
#endif