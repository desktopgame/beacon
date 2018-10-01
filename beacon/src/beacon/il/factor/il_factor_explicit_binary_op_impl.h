#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct il_factor;
struct enviroment;
struct generic_type;

typedef struct il_factor_explicit_binary_op {
	struct il_factor* receiver;
	struct il_factor* arg;
	operator_type type;
	int index;
} il_factor_explicit_binary_op;

struct il_factor* WrapILExplicitBinaryOp(il_factor_explicit_binary_op* self);

il_factor_explicit_binary_op* NewILExplicitBinaryOp(operator_type type);

void GenerateILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct enviroment* env, call_context* cctx);

void LoadILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct enviroment* env, call_context* cctx);

struct generic_type* EvalILExplicitBinaryOp(il_factor_explicit_binary_op* self, struct enviroment* env, call_context* cctx);

void DeleteILExplicitBinaryOp(il_factor_explicit_binary_op* self);
#endif