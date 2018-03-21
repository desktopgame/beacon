#pragma once
#ifndef SIGNAL_AST_ASSIGN_OPERATOR_TYPE_H
#define SIGNAL_AST_ASSIGN_OPERATOR_TYPE_H
/**
 * 代入演算子の種類.
 */
typedef enum assign_operator_type {
	assign_otype_def,
	assign_otype_add,
	assign_otype_sub,
	assign_otype_mul,
	assign_otype_div,
	assign_otype_mod,
} assign_operator_type;
#endif // !SIGNAL_AST_ASSIGN_OPERATOR_TYPE_H
