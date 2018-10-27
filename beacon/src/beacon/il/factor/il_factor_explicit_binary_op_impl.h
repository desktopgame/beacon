#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct ILFactor;
struct Enviroment;
struct GenericType;

typedef struct ILFactor_explicit_binary_op {
	struct ILFactor* receiver;
	struct ILFactor* arg;
	OperatorType type;
	int index;
} ILFactor_explicit_binary_op;

struct ILFactor* WrapILExplicitBinaryOp(ILFactor_explicit_binary_op* self);

ILFactor_explicit_binary_op* NewILExplicitBinaryOp(OperatorType type);

void GenerateILExplicitBinaryOp(ILFactor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILExplicitBinaryOp(ILFactor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

struct GenericType* EvalILExplicitBinaryOp(ILFactor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExplicitBinaryOp(ILFactor_explicit_binary_op* self);
#endif