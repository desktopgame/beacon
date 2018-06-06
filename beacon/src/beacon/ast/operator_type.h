#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>
#include <stdbool.h>

typedef enum operator_category {
	operator_carithmeric,
	operator_clogic,
	operator_ccompare,
} operator_category;

typedef enum operator_type {
	operator_add,
	operator_sub,
	operator_mul,
	operator_div,
	operator_mod,

	operator_bit_or,
	operator_bit_and,

	operator_logic_or,
	operator_logic_and,

	operator_eq,
	operator_noteq,

	operator_gt,
	operator_ge,
	operator_lt,
	operator_le,
	operator_lshift,
	operator_rshift,
	operator_excor,
} operator_type;

void operator_fprintf(operator_type self, FILE* fp);

char* operator_tostring(operator_type self);

bool operator_arithmetic(operator_type self);

bool operator_bit(operator_type self);

bool operator_logic(operator_type self);

bool operator_compare(operator_type self);

bool operator_shift(operator_type self);

bool operator_arg2(operator_type self);

bool operator_arg1(operator_type self);
#endif