#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#include "../../ast/operator_type.h"

//struct opcode_buf;
struct il_factor_childa_op;
struct il_factor_negative_op;
struct il_factor_not_op;

/**
 * 単項演算子を表す要素.
 */
typedef struct il_factor_unary_op {
	OperatorType type;
	OperatorCategory category;
	il_factor* a;
	union {
		struct il_factor_childa_op* childa_op;
		struct il_factor_negative_op* negative_op;
		struct il_factor_not_op* not_op;
	} u;
} il_factor_unary_op;

il_factor* WrapILUnaryOp(il_factor_unary_op* self);

il_factor_unary_op* NewILUnaryOp(OperatorType type);

void GenerateILUnaryOp(il_factor_unary_op* self, Enviroment* env, CallContext* cctx);

void LoadILUnaryOp(il_factor_unary_op* self, Enviroment* env, CallContext* cctx);

generic_type* EvalILUnaryOp(il_factor_unary_op* self, Enviroment* env, CallContext* cctx);

char* ILUnaryOpToString(il_factor_unary_op* self, Enviroment* env);

void DeleteILUnaryOp(il_factor_unary_op* self);

char* ILUnaryOpToString_simple(il_factor_unary_op* self, Enviroment* env);

int GetIndexILUnaryOp(il_factor_unary_op* self, Enviroment* env, CallContext* cctx);

int GetIndexILUnaryOp2(il_factor* receiver, OperatorType otype, Enviroment* env, CallContext* cctx);

generic_type* ApplyILUnaryOp(il_factor_unary_op* self, generic_type* gtype, Enviroment* env, CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
