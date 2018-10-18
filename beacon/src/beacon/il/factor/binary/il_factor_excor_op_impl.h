#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct generic_type;
struct Enviroment;

typedef struct il_factor_excor_op {
	struct il_factor_binary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_excor_op;

il_factor_excor_op* NewILExcorOp(operator_type type);

struct generic_type* EvalILExcorOp(il_factor_excor_op * self, struct Enviroment * env, call_context* cctx);

void GenerateILExcorOp(il_factor_excor_op* self, struct Enviroment* env, call_context* cctx);

void LoadILExcorOp(il_factor_excor_op* self, struct Enviroment* env, call_context* cctx);

void DeleteILExcorOp(il_factor_excor_op* self);

char* ILExcorOpToString(il_factor_excor_op* self, struct Enviroment* env);
#endif