#pragma once
#ifndef BEACON_IL_IL_FACTOR_BINARY_OP_H
#define BEACON_IL_IL_FACTOR_BINARY_OP_H
#include "../il_factor_interface.h"
#include "../../ast/operator_type.h"
#include <stdbool.h>

#define IL_FACT2BIN(fact) (il_factor_cast_binary_op(fact))

struct il_factor_arithmetic_op;
struct il_factor_logic_op;
struct il_factor_compare_op;
struct il_factor_shift_op;

/**
 * 二項演算子を表す要素.
 */
typedef struct il_factor_binary_op {
	operator_type type;
	operator_category category;
	il_factor* left;
	il_factor* right;
	bool load;
	union {
		struct il_factor_arithmetic_op* arithmetic_op;
		struct il_factor_logic_op* logic_op;
		struct il_factor_compare_op* compare_op;
		struct il_factor_shift_op* shift_op;
	} u;
} il_factor_binary_op;

il_factor* il_factor_wrap_binary(il_factor_binary_op* self);

il_factor_binary_op* il_factor_binary_op_new(operator_type type);

void il_factor_binary_op_dump(il_factor_binary_op* self, int depth);

void il_factor_binary_op_generate(il_factor_binary_op* self, struct enviroment* env);

void il_factor_binary_op_load(il_factor_binary_op* self, struct enviroment* env);

generic_type* il_factor_binary_op_eval(il_factor_binary_op* self, struct enviroment* env);

char* il_factor_binary_op_tostr(il_factor_binary_op* self, struct enviroment* env);

void il_factor_binary_op_delete(il_factor_binary_op* self);

il_factor_binary_op* il_factor_cast_binary_op(il_factor* fact);

char* il_factor_binary_op_tostr_simple(il_factor_binary_op* self, struct enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_BINARY_OP_H
