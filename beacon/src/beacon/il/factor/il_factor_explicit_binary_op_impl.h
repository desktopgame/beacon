#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
struct il_factor;
struct enviroment;
struct generic_type;

typedef struct il_factor_explicit_binary_op {
	struct il_factor* receiver;
	struct il_factor* arg;
	operator_type type;
	int index;
} il_factor_explicit_binary_op;

struct il_factor* il_factor_wrap_explicit_binary_op(il_factor_explicit_binary_op* self);

il_factor_explicit_binary_op* il_factor_explicit_binary_op_new(operator_type type);

void il_factor_explicit_binary_op_dump(il_factor_explicit_binary_op* self, int depth);

void il_factor_explicit_binary_op_generate(il_factor_explicit_binary_op* self, struct enviroment* env);

void il_factor_explicit_binary_op_load(il_factor_explicit_binary_op* self, struct enviroment* env);

struct generic_type* il_factor_explicit_binary_op_eval(il_factor_explicit_binary_op* self, struct enviroment* env);

void il_factor_explicit_binary_op_delete(il_factor_explicit_binary_op* self);
#endif