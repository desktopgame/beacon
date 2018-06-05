#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>

typedef enum operator_type {
	operator_add,
	operator_sub,
	operator_mul,
	operator_div,
	operator_mod,
} operator_type;

void operator_fprintf(operator_type self, FILE* fp);
#endif