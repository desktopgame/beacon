#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct GenericType;
struct Enviroment;
struct il_factor_binary_op;
typedef struct il_factor_shift_op {
	struct il_factor_binary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_shift_op;

il_factor_shift_op* NewILShiftOp(OperatorType type);

struct GenericType* EvalILShiftOp(il_factor_shift_op * self, struct Enviroment* env, CallContext* cctx);

void GenerateILShiftOp(il_factor_shift_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILShiftOp(il_factor_shift_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILShiftOp(il_factor_shift_op* self);

char* ILShiftOpToString(il_factor_shift_op* self, struct Enviroment* env);
#endif