#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_UNARY_OP_H
#define SIGNAL_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
/**
 * 単項演算子の種類を表す列挙型.
 */
typedef enum ilunary_op_type {
	ilunary_not,
	ilunary_neg
} ilunary_op_type;

/**
 * 単項演算子を表す要素.
 */
typedef struct il_factor_unary_op {
	ilunary_op_type type;
	il_factor* a;
} il_factor_unary_op;

/**
 * 単項演算子をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_unary(il_factor_unary_op* self);

/**
 * 単項演算子を作成します.
 * @param type
 * @return
 */
il_factor_unary_op* il_factor_unary_op_new(ilunary_op_type type);

/**
 * 単項演算子を出力します.
 * @param self
 * @param depth
 */
void il_factor_unary_op_dump(il_factor_unary_op* self, int depth);

/**
 * 単項演算子を開放します.
 * @param self
 */
void il_factor_unary_op_delete(il_factor_unary_op* self);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
