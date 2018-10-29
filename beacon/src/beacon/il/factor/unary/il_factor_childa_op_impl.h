#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILUnaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILChildaOp {
	struct ILUnaryOp* Parent;
	OperatorType Type;
	int OperatorIndex;
} ILChildaOp;

ILChildaOp* NewILChildaOp(OperatorType type);

struct GenericType* EvalILChildaOp(ILChildaOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILChildaOp(ILChildaOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILChildaOp(ILChildaOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILChildaOp(ILChildaOp* self);

char* ILChildaOpToString(ILChildaOp* self, struct Enviroment* env);
#endif