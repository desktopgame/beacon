#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct il_factor;
struct Enviroment;
struct GenericType;

typedef struct il_factor_explicit_binary_op {
	struct il_factor* receiver;
	struct il_factor* arg;
	OperatorType type;
	int index;
} il_factor_explicit_binary_op;

struct il_factor* WrapILExplicitBinaryOp(il_factor_explicit_binary_op* self);

il_factor_explicit_binary_op* NewILExplicitBinaryOp(OperatorType type);

void GenerateILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

struct GenericType* EvalILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExplicitBinaryOp(il_factor_explicit_binary_op* self);
#endif