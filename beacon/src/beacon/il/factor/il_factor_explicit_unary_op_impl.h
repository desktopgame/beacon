#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
struct il_factor;

typedef struct il_factor_explicit_unary_op {
	struct il_factor* receiver;
	operator_type type;
} il_factor_explicit_unary_op;

il_factor_explicit_unary_op* il_factor_explicit_unary_op_new(operator_type type);

void il_factor_explicit_unary_op_delete(il_factor_explicit_unary_op* self);
#endif