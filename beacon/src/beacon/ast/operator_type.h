#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>
#include <stdbool.h>

typedef enum operator_type {
	operator_add,
	operator_sub,
	operator_mul,
	operator_div,
	operator_mod,
} operator_type;

void operator_fprintf(operator_type self, FILE* fp);

char* operator_tostring(operator_type self);

bool operator_arg2(operator_type self);

bool operator_arg1(operator_type self);
#endif