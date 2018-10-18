#pragma once
#ifndef BEACON_IL_IL_FACTOR_BINARY_OP_H
#define BEACON_IL_IL_FACTOR_BINARY_OP_H
#include "../il_factor_interface.h"
#include "../../ast/operator_type.h"
#include <stdbool.h>

struct il_factor_arithmetic_op;
struct il_factor_logic_op;
struct il_factor_compare_op;
struct il_factor_shift_op;
struct il_factor_excor_op;

/**
 * 二項演算子を表す要素.
 */
typedef struct il_factor_binary_op {
	operator_type type;
	operator_category category;
	il_factor* left;
	il_factor* right;
	bool load;
	union {
		struct il_factor_arithmetic_op* arithmetic_op;
		struct il_factor_logic_op* logic_op;
		struct il_factor_compare_op* compare_op;
		struct il_factor_shift_op* shift_op;
		struct il_factor_excor_op* excor_op;
	} u;
} il_factor_binary_op;

il_factor* WrapILBinaryOp(il_factor_binary_op* self);

il_factor_binary_op* NewILBinaryOp(operator_type type);

void GenerateILBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

void LoadILBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

generic_type* EvalILBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

char* ILBinaryOpToString(il_factor_binary_op* self, Enviroment* env);

void DeleteILBinaryOp(il_factor_binary_op* self);

char* ILBinaryOpToString_simple(il_factor_binary_op* self, Enviroment* env);

bool IsIntIntBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

bool IsDoubleDoubleBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

bool IsBoolBoolBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

bool IsCharCharBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

int GetIndexILBinaryOp(il_factor_binary_op* self, Enviroment* env, call_context* cctx);

int GetIndexILBinaryOp2(il_factor* receiver, il_factor* arg, operator_type otype, Enviroment* env, call_context* cctx);

generic_type* ApplyILBinaryOp(il_factor_binary_op* self, generic_type* gtype, Enviroment* env, call_context* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_BINARY_OP_H
