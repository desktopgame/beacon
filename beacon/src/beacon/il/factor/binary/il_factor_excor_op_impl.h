#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILBinaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILExcorOp {
	struct ILBinaryOp* Parent;
	OperatorType Type;
	int OperatorIndex;
} ILExcorOp;

ILExcorOp* NewILExcorOp(OperatorType type);

struct GenericType* EvalILExcorOp(ILExcorOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILExcorOp(ILExcorOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILExcorOp(ILExcorOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExcorOp(ILExcorOp* self);

char* ILExcorOpToString(ILExcorOp* self, struct Enviroment* env);
#endif