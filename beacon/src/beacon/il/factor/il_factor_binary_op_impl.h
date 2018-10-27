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
typedef struct ILBinaryOp {
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
} ILBinaryOp;

ILFactor* WrapILBinaryOp(ILBinaryOp* self);

ILBinaryOp* NewILBinaryOp(OperatorType type);

void GenerateILBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

void LoadILBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

char* ILBinaryOpToString(ILBinaryOp* self, Enviroment* env);

void DeleteILBinaryOp(ILBinaryOp* self);

char* ILBinaryOpToString_simple(ILBinaryOp* self, Enviroment* env);

bool IsIntIntBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

bool IsDoubleDoubleBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

bool IsBoolBoolBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

bool IsCharCharBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

int GetIndexILBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx);

int GetIndexILBinaryOp2(ILFactor* receiver, ILFactor* arg, OperatorType otype, Enviroment* env, CallContext* cctx);

GenericType* ApplyILBinaryOp(ILBinaryOp* self, GenericType* gtype, Enviroment* env, CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_BINARY_OP_H
