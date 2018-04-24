#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#define IL_FACT2U(fact) (il_factor_cast_unary_op(fact))
//struct opcode_buf;
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

il_factor* il_factor_wrap_unary(il_factor_unary_op* self);

il_factor_unary_op* il_factor_unary_op_new(ilunary_op_type type);

void il_factor_unary_op_dump(il_factor_unary_op* self, int depth);

void il_factor_unary_op_generate(il_factor_unary_op* self, struct enviroment* env, il_context* ilctx);

void il_factor_unary_op_load(il_factor_unary_op* self, struct enviroment* env, il_context* ilctx);

generic_type* il_factor_unary_op_eval(il_factor_unary_op* self, struct enviroment* env, il_context* ilctx);

char* il_factor_unary_op_tostr(il_factor_unary_op* self, struct enviroment* env, il_context* ilctx);

void il_factor_unary_op_delete(il_factor_unary_op* self);

il_factor_unary_op* il_factor_cast_unary_op(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
