#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_EXCOP_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct il_factor_binary_op;
struct generic_type;
struct enviroment;

typedef struct il_factor_excor_op {
	struct il_factor_binary_op* parent;
	operator_type type;
	int operator_index;
} il_factor_excor_op;

il_factor_excor_op* il_factor_excor_op_new(operator_type type);

void il_factor_excor_op_dump(il_factor_excor_op* self, int depth);

struct generic_type* il_factor_excor_op_eval(il_factor_excor_op * self, struct enviroment * env, call_context* cctx);

void il_factor_excor_op_generate(il_factor_excor_op* self, struct enviroment* env, call_context* cctx);

void il_factor_excor_op_load(il_factor_excor_op* self, struct enviroment* env, call_context* cctx);

void il_factor_excor_op_delete(il_factor_excor_op* self);

char* il_factor_excor_op_tostr(il_factor_excor_op* self, struct enviroment* env);
#endif