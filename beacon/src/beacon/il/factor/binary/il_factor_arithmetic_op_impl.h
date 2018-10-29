#ifndef BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#define BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct GenericType;
struct Enviroment;
typedef struct ILArithmeticOp {
	struct ILBinaryOp* parent;
	int operator_index;
	OperatorType type;
} ILArithmeticOp;

ILArithmeticOp* NewILArithmeticOp(OperatorType type);


struct GenericType* EvalILArithmeticOp(ILArithmeticOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILArithmeticOp(ILArithmeticOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILArithmeticOp(ILArithmeticOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILArithmeticOp(ILArithmeticOp* self);

char* ILArithmeticOpToString(ILArithmeticOp* self, struct Enviroment* env);
#endif