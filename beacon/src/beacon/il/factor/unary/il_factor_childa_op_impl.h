#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
struct il_factor_unary_op;
struct generic_type;
struct enviroment;

typedef struct il_factor_childa_op {
	struct il_factor_unary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_childa_op;

il_factor_childa_op* il_factor_childa_op_new(operator_type type);

void il_factor_childa_op_dump(il_factor_childa_op* self, int depth);

struct generic_type* il_factor_childa_op_eval(il_factor_childa_op * self, struct enviroment * env);

void il_factor_childa_op_generate(il_factor_childa_op* self, struct enviroment* env);

void il_factor_childa_op_load(il_factor_childa_op* self, struct enviroment* env);

void il_factor_childa_op_delete(il_factor_childa_op* self);

char* il_factor_childa_op_tostr(il_factor_childa_op* self, struct enviroment* env);
#endif