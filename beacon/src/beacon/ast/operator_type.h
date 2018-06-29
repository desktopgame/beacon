#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>
#include <stdbool.h>

/**
 * 演算子のカテゴリを表す列挙.
 */
typedef enum operator_category {
	operator_carithmeric,
	operator_clogic,
	operator_ccompare,
	operator_cshift,
	operator_cchilda,
	operator_cnegative,
	operator_cnot,
	operator_cexcor
} operator_category;

/**
 * 演算子の種類を表す列挙.
 */
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

	operator_childa,
	operator_negative,
	operator_not,
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