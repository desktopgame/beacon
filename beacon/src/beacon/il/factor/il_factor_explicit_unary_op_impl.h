#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_UNARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct il_factor;
struct enviroment;
struct generic_type;

typedef struct il_factor_explicit_unary_op {
	struct il_factor* receiver;
	operator_type type;
	int index;
} il_factor_explicit_unary_op;

struct il_factor* WrapILExplicitUnaryOp(il_factor_explicit_unary_op* self);

il_factor_explicit_unary_op* NewILExplicitUnaryOp(operator_type type);

void GenerateILExplicitUnaryOp(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

void LoadILExplicitUnaryOp(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

struct generic_type* EvalILExplicitUnaryOp(il_factor_explicit_unary_op* self, struct enviroment* env, call_context* cctx);

void DeleteILExplicitUnaryOp(il_factor_explicit_unary_op* self);
#endif