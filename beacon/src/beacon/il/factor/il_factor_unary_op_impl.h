#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#include "../../ast/operator_type.h"

//struct opcode_buf;
struct ILChildaOp;
struct ILNegativeOp;
struct ILNotOp;

/**
 * 単項演算子を表す要素.
 */
typedef struct ILUnaryOp {
	OperatorType Type;
	OperatorCategory Category;
	ILFactor* Arg;
	union {
		struct ILChildaOp* ChildaOp;
		struct ILNegativeOp* NegativeOp;
		struct ILNotOp* NotOp;
	} Kind;
} ILUnaryOp;

ILFactor* WrapILUnaryOp(ILUnaryOp* self);

ILUnaryOp* NewILUnaryOp(OperatorType type);

void GenerateILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx);

void LoadILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx);

char* ILUnaryOpToString(ILUnaryOp* self, Enviroment* env);

void DeleteILUnaryOp(ILUnaryOp* self);

char* ILUnaryOpToString_simple(ILUnaryOp* self, Enviroment* env);

int GetIndexILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx);

int GetIndexILUnaryOp2(ILFactor* receiver, OperatorType otype, Enviroment* env, CallContext* cctx);

GenericType* ApplyILUnaryOp(ILUnaryOp* self, GenericType* gtype, Enviroment* env, CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
