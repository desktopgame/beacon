#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct GenericType;
struct Enviroment;
struct ILFactor_binary_op;
typedef struct ILFactor_shift_op {
	struct ILFactor_binary_op* parent;
	OperatorType type;
	int operator_index;
} ILFactor_shift_op;

ILFactor_shift_op* NewILShiftOp(OperatorType type);

struct GenericType* EvalILShiftOp(ILFactor_shift_op * self, struct Enviroment* env, CallContext* cctx);

void GenerateILShiftOp(ILFactor_shift_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILShiftOp(ILFactor_shift_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILShiftOp(ILFactor_shift_op* self);

char* ILShiftOpToString(ILFactor_shift_op* self, struct Enviroment* env);
#endif