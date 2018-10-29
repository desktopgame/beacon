#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct ILFactor;
struct Enviroment;
struct GenericType;

typedef struct ILExplicitUnaryOp {
	struct ILFactor* Receiver;
	OperatorType Type;
	int Index;
} ILExplicitUnaryOp;

struct ILFactor* WrapILExplicitUnaryOp(ILExplicitUnaryOp* self);

ILExplicitUnaryOp* NewILExplicitUnaryOp(OperatorType type);

void GenerateILExplicitUnaryOp(ILExplicitUnaryOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILExplicitUnaryOp(ILExplicitUnaryOp* self, struct Enviroment* env, CallContext* cctx);

struct GenericType* EvalILExplicitUnaryOp(ILExplicitUnaryOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExplicitUnaryOp(ILExplicitUnaryOp* self);
#endif