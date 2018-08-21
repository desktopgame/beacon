#pragma once
#ifndef BEACON_AST_ASSIGN_OPERATOR_TYPE_H
#define BEACON_AST_ASSIGN_OPERATOR_TYPE_H
/**
 * 代入演算子の種類.
 */
typedef enum assign_operator_type {
	assign_otype_def_T,
	assign_otype_add_T,
	assign_otype_sub_T,
	assign_otype_mul_T,
	assign_otype_div_T,
	assign_otype_mod_T,
} assign_operator_type;
#endif // !SIGNAL_AST_ASSIGN_OPERATOR_TYPE_H
