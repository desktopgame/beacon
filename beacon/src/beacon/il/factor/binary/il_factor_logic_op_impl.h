#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"

struct ILBinaryOp;
struct GenericType;
struct Enviroment;
typedef struct ILFactor_logic_op {
	struct ILBinaryOp* parent;
	OperatorType type;
	int operator_index;
} ILFactor_logic_op;

ILFactor_logic_op* NewILLogicOp(OperatorType type);

struct GenericType* EvalILLogicOp(ILFactor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void GenerateILLogicOp(ILFactor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILLogicOp(ILFactor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILLogicOp(ILFactor_logic_op* self);

char* ILLogicOpToString(ILFactor_logic_op* self, struct Enviroment* env);
#endif