#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct GenericType;
struct Enviroment;
struct ILBinaryOp;
typedef struct ILShiftOp {
	struct ILBinaryOp* parent;
	OperatorType type;
	int operator_index;
} ILShiftOp;

ILShiftOp* NewILShiftOp(OperatorType type);

struct GenericType* EvalILShiftOp(ILShiftOp * self, struct Enviroment* env, CallContext* cctx);

void GenerateILShiftOp(ILShiftOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILShiftOp(ILShiftOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILShiftOp(ILShiftOp* self);

char* ILShiftOpToString(ILShiftOp* self, struct Enviroment* env);
#endif