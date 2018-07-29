#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#include "../../ast/operator_type.h"
#define IL_FACT2U(fact) (il_factor_cast_unary_op(fact))
//struct opcode_buf;
struct il_factor_childa_op;
struct il_factor_negative_op;
struct il_factor_not_op;

/**
 * 単項演算子を表す要素.
 */
typedef struct il_factor_unary_op {
	operator_type type;
	operator_category category;
	il_factor* a;
	union {
		struct il_factor_childa_op* childa_op;
		struct il_factor_negative_op* negative_op;
		struct il_factor_not_op* not_op;
	} u;
} il_factor_unary_op;

il_factor* il_factor_wrap_unary(il_factor_unary_op* self);

il_factor_unary_op* il_factor_unary_op_new(operator_type type);

void il_factor_unary_op_dump(il_factor_unary_op* self, int depth);

void il_factor_unary_op_generate(il_factor_unary_op* self, struct enviroment* env, call_context* cctx);

void il_factor_unary_op_load(il_factor_unary_op* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_unary_op_eval(il_factor_unary_op* self, struct enviroment* env, call_context* cctx);

char* il_factor_unary_op_tostr(il_factor_unary_op* self, struct enviroment* env);

void il_factor_unary_op_delete(il_factor_unary_op* self);

char* il_factor_unary_op_tostr_simple(il_factor_unary_op* self, struct enviroment* env);

il_factor_unary_op* il_factor_cast_unary_op(il_factor* fact);

int il_factor_unary_op_index(il_factor_unary_op* self, struct enviroment* env, call_context* cctx);

int il_factor_unary_op_index2(il_factor* receiver, operator_type otype, struct enviroment* env, call_context* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
