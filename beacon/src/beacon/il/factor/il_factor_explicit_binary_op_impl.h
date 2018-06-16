#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
struct il_factor;

typedef struct il_factor_explicit_binary_op {
	struct il_factor* receiver;
	struct il_factor* arg;
	operator_type type;
} il_factor_explicit_binary_op;

struct il_factor* il_factor_wrap_explicit_binary_op(il_factor_explicit_binary_op* self);

il_factor_explicit_binary_op* il_factor_explicit_binary_op_new(operator_type type);

void il_factor_explicit_binary_op_delete(il_factor_explicit_binary_op* self);
#endif