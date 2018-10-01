#ifndef BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#define BEACON_IL_FACTOR_BIN_IL_FACTOR_ARITHMETIC_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct generic_type;
struct enviroment;
typedef struct il_factor_arithmetic_op {
	struct il_factor_binary_op* parent;
	int operator_index;
	operator_type type;
} il_factor_arithmetic_op;

il_factor_arithmetic_op* NewILArithmeticOp(operator_type type);


struct generic_type* EvalILArithmeticOp(il_factor_arithmetic_op * self, struct enviroment * env, call_context* cctx);

void GenerateILArithmeticOp(il_factor_arithmetic_op* self, struct enviroment* env, call_context* cctx);

void LoadILArithmeticOp(il_factor_arithmetic_op* self, struct enviroment* env, call_context* cctx);

void DeleteILArithmeticOp(il_factor_arithmetic_op* self);

char* ILArithmeticOpToString(il_factor_arithmetic_op* self, struct enviroment* env);
#endif