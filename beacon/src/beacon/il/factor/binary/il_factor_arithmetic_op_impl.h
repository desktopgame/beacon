#ifndef BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#define BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILFactor_binary_op;
struct GenericType;
struct Enviroment;
typedef struct ILFactor_arithmetic_op {
	struct ILFactor_binary_op* parent;
	int operator_index;
	OperatorType type;
} ILFactor_arithmetic_op;

ILFactor_arithmetic_op* NewILArithmeticOp(OperatorType type);


struct GenericType* EvalILArithmeticOp(ILFactor_arithmetic_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILArithmeticOp(ILFactor_arithmetic_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILArithmeticOp(ILFactor_arithmetic_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILArithmeticOp(ILFactor_arithmetic_op* self);

char* ILArithmeticOpToString(ILFactor_arithmetic_op* self, struct Enviroment* env);
#endif