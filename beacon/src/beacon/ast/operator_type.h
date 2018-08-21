#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>
#include <stdbool.h>

/**
 * 演算子のカテゴリを表す列挙.
 */
typedef enum operator_category {
	operator_carithmeric_T,
	operator_clogic_T,
	operator_ccompare_T,
	operator_cshift_T,
	operator_cchilda_T,
	operator_cnegative_T,
	operator_cnot_T,
	operator_cexcor_T,
} operator_category;

/**
 * 演算子の種類を表す列挙.
 */
typedef enum operator_type {
	operator_add_T,
	operator_sub_T,
	operator_mul_T,
	operator_div_T,
	operator_mod_T,

	operator_bit_or_T,
	operator_bit_and_T,

	operator_logic_or_T,
	operator_logic_and_T,

	operator_eq_T,
	operator_not_Teq_T,

	operator_gt_T,
	operator_ge_T,
	operator_lt_T,
	operator_le_T,
	operator_lshift_T,
	operator_rshift_T,
	operator_excor_T,

	operator_childa_T,
	operator_negative_T,
	operator_not_T,

	operator_sub_script_set_T,
	operator_sub_script_get_T,
} operator_type;
/**
 * オペレータを文字列として出力します.
 * @param fp
 * @param self
 */
void operator_fprintf(FILE* fp, operator_type self);

/**
 * オペレータを文字列にして返します.
 * @param self
 * @return
 */
char* operator_tostring(operator_type self);

/**
 * オペレータが算術演算子なら true.
 * @param self
 * @return
 */
bool operator_arithmetic(operator_type self);

/**
 * オペレータがビット演算子なら true.
 * @param self
 * @return
 */
bool operator_bit(operator_type self);

/**
 * オペレータが論理演算子なら true.
 * @param self
 * @return
 */
bool operator_logic(operator_type self);

/**
 * オペレータが比較演算子なら true.
 * @param self
 * @return
 */
bool operator_compare(operator_type self);

/**
 * オペレータがシフト演算子なら true.
 * @param self
 * @return
 */
bool operator_shift(operator_type self);

/**
 * オペレータが二項演算子なら true.
 * @param self
 * @return
 */
bool operator_arg2(operator_type self);

/**
 * オペレータが単項演算子なら true.
 * @param self
 * @return
 */
bool operator_arg1(operator_type self);
#endif