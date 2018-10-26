#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct GenericType;
struct Enviroment;

typedef struct il_factor_excor_op {
	struct il_factor_binary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_excor_op;

il_factor_excor_op* NewILExcorOp(OperatorType type);

struct GenericType* EvalILExcorOp(il_factor_excor_op * self, struct Enviroment * env, CallContext* cctx);

void GenerateILExcorOp(il_factor_excor_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILExcorOp(il_factor_excor_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExcorOp(il_factor_excor_op* self);

char* ILExcorOpToString(il_factor_excor_op* self, struct Enviroment* env);
#endif