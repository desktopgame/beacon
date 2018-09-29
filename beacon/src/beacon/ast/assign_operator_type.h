#pragma once
#ifndef BEACON_AST_ASSIGN_OPERATOR_TYPE_H
#define BEACON_AST_ASSIGN_OPERATOR_TYPE_H
/**
 * 代入演算子の種類.
 */
typedef enum assign_operator_type {
	ASSIGN_OTYPE_DEF_T,
	ASSIGN_OTYPE_ADD_T,
	ASSIGN_OTYPE_SUB_T,
	ASSIGN_OTYPE_MUL_T,
	ASSIGN_OTYPE_DIV_T,
	ASSIGN_OTYPE_MOD_T,
} assign_operator_type;
#endif // !SIGNAL_AST_ASSIGN_OPERATOR_TYPE_H
