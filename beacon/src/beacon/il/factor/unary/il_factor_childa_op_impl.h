#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILFactor_unary_op;
struct GenericType;
struct Enviroment;

typedef struct ILFactor_childa_op {
	struct ILFactor_unary_op* parent;
	OperatorType type;
	int operator_index;
} ILFactor_childa_op;

ILFactor_childa_op* NewILChildaOp(OperatorType type);

struct GenericType* EvalILChildaOp(ILFactor_childa_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILChildaOp(ILFactor_childa_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILChildaOp(ILFactor_childa_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILChildaOp(ILFactor_childa_op* self);

char* ILChildaOpToString(ILFactor_childa_op* self, struct Enviroment* env);
#endif