#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct ILFactor;
struct Enviroment;
struct GenericType;

typedef struct ILFactor_explicit_unary_op {
	struct ILFactor* receiver;
	OperatorType type;
	int index;
} ILFactor_explicit_unary_op;

struct ILFactor* WrapILExplicitUnaryOp(ILFactor_explicit_unary_op* self);

ILFactor_explicit_unary_op* NewILExplicitUnaryOp(OperatorType type);

void GenerateILExplicitUnaryOp(ILFactor_explicit_unary_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILExplicitUnaryOp(ILFactor_explicit_unary_op* self, struct Enviroment* env, CallContext* cctx);

struct GenericType* EvalILExplicitUnaryOp(ILFactor_explicit_unary_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExplicitUnaryOp(ILFactor_explicit_unary_op* self);
#endif