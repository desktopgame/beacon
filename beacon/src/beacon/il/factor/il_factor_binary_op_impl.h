#pragma once
#ifndef BEACON_IL_IL_FACTOR_BINARY_OP_H
#define BEACON_IL_IL_FACTOR_BINARY_OP_H
#include "../il_factor_interface.h"

#define IL_FACT2BIN(fact) (il_factor_cast_binary_op(fact))
/**
 * 二項演算子の種類を表す列挙型.
 */
typedef enum ilbinary_op_type {
	ilbinary_add,
	ilbinary_sub,
	ilbinary_mul,
	ilbinary_div,
	ilbinary_mod,

	ilbinary_bit_or,
	ilbinary_logic_or,

	ilbinary_bit_and,
	ilbinary_logic_and,

	ilbinary_eq,
	ilbinary_noteq,
	ilbinary_gt,
	ilbinary_ge,
	ilbinary_lt,
	ilbinary_le,

	ilbinary_assign,
	ilbinary_add_assign,
	ilbinary_sub_assign,
	ilbinary_mul_assign,
	ilbinary_div_assign,
	ilbinary_mod_assign,
} ilbinary_op_type;

/**
 * 二項演算子を表す要素.
 */
typedef struct il_factor_binary_op {
	ilbinary_op_type type;
	il_factor* left;
	il_factor* right;
} il_factor_binary_op;

/**
 * 二項演算子をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_binary(il_factor_binary_op* self);

/**
 * 二項演算子を作成します.
 * @param type
 * @return
 */
il_factor_binary_op* il_factor_binary_op_new(ilbinary_op_type type);

/**
 * 二項演算子を出力します.
 * @param self
 * @param depth
 */
void il_factor_binary_op_dump(il_factor_binary_op* self, int depth);

/**
 * 二項演算子を生成します.
 * @param self
 * @param env
 */
void il_factor_binary_op_generate(il_factor_binary_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 二項演算子を読み込みます.
 * @param self
 * @parma env
 * @param eh
 */
void il_factor_binary_op_load(il_factor_binary_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 二項演算子の結果の型を返します.
 * @param self
 * @param env
 * @return
 */
generic_type* il_factor_binary_op_eval(il_factor_binary_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 二項演算子を開放します.
 * @param self
 */
void il_factor_binary_op_delete(il_factor_binary_op* self);

il_factor_binary_op* il_factor_cast_binary_op(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_BINARY_OP_H
