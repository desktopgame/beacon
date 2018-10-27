#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#include "../../ast/operator_type.h"

//struct opcode_buf;
struct ILFactor_childa_op;
struct ILFactor_negative_op;
struct ILFactor_not_op;

/**
 * 単項演算子を表す要素.
 */
typedef struct ILFactor_unary_op {
	OperatorType type;
	OperatorCategory category;
	ILFactor* a;
	union {
		struct ILFactor_childa_op* childa_op;
		struct ILFactor_negative_op* negative_op;
		struct ILFactor_not_op* not_op;
	} u;
} ILFactor_unary_op;

ILFactor* WrapILUnaryOp(ILFactor_unary_op* self);

ILFactor_unary_op* NewILUnaryOp(OperatorType type);

void GenerateILUnaryOp(ILFactor_unary_op* self, Enviroment* env, CallContext* cctx);

void LoadILUnaryOp(ILFactor_unary_op* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILUnaryOp(ILFactor_unary_op* self, Enviroment* env, CallContext* cctx);

char* ILUnaryOpToString(ILFactor_unary_op* self, Enviroment* env);

void DeleteILUnaryOp(ILFactor_unary_op* self);

char* ILUnaryOpToString_simple(ILFactor_unary_op* self, Enviroment* env);

int GetIndexILUnaryOp(ILFactor_unary_op* self, Enviroment* env, CallContext* cctx);

int GetIndexILUnaryOp2(ILFactor* receiver, OperatorType otype, Enviroment* env, CallContext* cctx);

GenericType* ApplyILUnaryOp(ILFactor_unary_op* self, GenericType* gtype, Enviroment* env, CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
