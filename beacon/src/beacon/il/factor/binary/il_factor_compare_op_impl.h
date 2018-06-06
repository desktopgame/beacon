#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_COMPARE_OP_IMPL_H
#include "../../../ast/operator_type.h"
struct il_factor_binary_op;
struct generic_type;
struct enviroment;
typedef struct il_factor_compare_op {
	struct il_factor_binary_op* parent;
	operator_type type;
} il_factor_compare_op;

il_factor_compare_op* il_factor_compare_op_new(operator_type type);

void il_factor_compare_op_dump(il_factor_compare_op* self, int depth);

struct generic_type* il_factor_compare_op_eval(il_factor_compare_op * self, struct enviroment * env);

void il_factor_compare_op_generate(il_factor_compare_op* self, struct enviroment* env);

void il_factor_compare_op_load(il_factor_compare_op* self, struct enviroment* env);

void il_factor_compare_op_delete(il_factor_compare_op* self);

char* il_factor_compare_op_tostr(il_factor_compare_op* self, struct enviroment* env);
#endif