#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#include "../../../ast/operator_type.h"

struct il_factor_binary_op;
typedef struct il_factor_logic_op {
	struct il_factor_binary_op* parent;
	operator_type type;
} il_factor_logic_op;

il_factor_logic_op* il_factor_logic_op_new(operator_type type);

void il_factor_logic_op_delete(il_factor_logic_op* self);
#endif