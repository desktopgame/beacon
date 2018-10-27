#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILFactor_excor_op {
	struct ILBinaryOp* parent;
	OperatorType type;
	int operator_index;
} ILFactor_excor_op;

ILFactor_excor_op* NewILExcorOp(OperatorType type);

struct GenericType* EvalILExcorOp(ILFactor_excor_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILExcorOp(ILFactor_excor_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILExcorOp(ILFactor_excor_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExcorOp(ILFactor_excor_op* self);

char* ILExcorOpToString(ILFactor_excor_op* self, struct Enviroment* env);
#endif