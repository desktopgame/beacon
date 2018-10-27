#pragma once
#ifndef BEACON_IL_IL_FACTOR_BINARY_OP_H
#define BEACON_IL_IL_FACTOR_BINARY_OP_H
#include "../il_factor_interface.h"
#include "../../ast/operator_type.h"
#include <stdbool.h>

struct ILFactor_arithmetic_op;
struct ILFactor_logic_op;
struct ILFactor_compare_op;
struct ILFactor_shift_op;
struct ILFactor_excor_op;

/**
 * 二項演算子を表す要素.
 */
typedef struct ILFactor_binary_op {
	OperatorType type;
	OperatorCategory category;
	ILFactor* left;
	ILFactor* right;
	bool load;
	union {
		struct ILFactor_arithmetic_op* arithmetic_op;
		struct ILFactor_logic_op* logic_op;
		struct ILFactor_compare_op* compare_op;
		struct ILFactor_shift_op* shift_op;
		struct ILFactor_excor_op* excor_op;
	} u;
} ILFactor_binary_op;

ILFactor* WrapILBinaryOp(ILFactor_binary_op* self);

ILFactor_binary_op* NewILBinaryOp(OperatorType type);

void GenerateILBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

void LoadILBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

char* ILBinaryOpToString(ILFactor_binary_op* self, Enviroment* env);

void DeleteILBinaryOp(ILFactor_binary_op* self);

char* ILBinaryOpToString_simple(ILFactor_binary_op* self, Enviroment* env);

bool IsIntIntBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

bool IsDoubleDoubleBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

bool IsBoolBoolBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

bool IsCharCharBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

int GetIndexILBinaryOp(ILFactor_binary_op* self, Enviroment* env, CallContext* cctx);

int GetIndexILBinaryOp2(ILFactor* receiver, ILFactor* arg, OperatorType otype, Enviroment* env, CallContext* cctx);

GenericType* ApplyILBinaryOp(ILFactor_binary_op* self, GenericType* gtype, Enviroment* env, CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_BINARY_OP_H
