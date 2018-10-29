#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct ILUnaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILNotOp {
	struct ILUnaryOp* Parent;
	OperatorType Type;
	int OperatorIndex;
} ILNotOp;

ILNotOp* NewILNotOp(OperatorType type);

struct GenericType* EvalILNotOp(ILNotOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNotOp(ILNotOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILNotOp(ILNotOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNotOp(ILNotOp* self);

char* ILNotOpToString(ILNotOp* self, struct Enviroment* env);
#endif