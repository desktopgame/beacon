#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct il_factor_unary_op;
struct GenericType;
struct Enviroment;

typedef struct il_factor_not_op {
	struct il_factor_unary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_not_op;

il_factor_not_op* NewILNotOp(OperatorType type);

struct GenericType* EvalILNotOp(il_factor_not_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNotOp(il_factor_not_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILNotOp(il_factor_not_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNotOp(il_factor_not_op* self);

char* ILNotOpToString(il_factor_not_op* self, struct Enviroment* env);
#endif