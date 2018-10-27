#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct ILFactor_unary_op;
struct GenericType;
struct Enviroment;

typedef struct ILFactor_not_op {
	struct ILFactor_unary_op* parent;
	OperatorType type;
	int operator_index;
} ILFactor_not_op;

ILFactor_not_op* NewILNotOp(OperatorType type);

struct GenericType* EvalILNotOp(ILFactor_not_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNotOp(ILFactor_not_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILNotOp(ILFactor_not_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNotOp(ILFactor_not_op* self);

char* ILNotOpToString(ILFactor_not_op* self, struct Enviroment* env);
#endif