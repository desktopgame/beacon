#ifndef BEACON_IL_il_factor_call_op_H
#define BEACON_IL_il_factor_call_op_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"

#define IL_FACT2CALL(fact) (il_factor_cast_call_op(fact))

struct enviroment;
struct generic_type;

typedef struct il_factor_call_op {
	il_factor* parent;
	il_factor* receiver;
	//vector* type_argument_list;
	vector* argument_list;
} il_factor_call_op;

il_factor* il_factor_wrap_call_op(il_factor_call_op* self);

il_factor_call_op* il_factor_call_op_new();

void il_factor_call_op_load(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

struct generic_type* il_factor_call_op_eval(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache);

void il_factor_call_op_generate(il_factor_call_op* self, struct enviroment* env, il_load_cache* cache);

void il_factor_call_op_delete(il_factor_call_op* self);

il_factor_call_op* il_factor_cast_call_op(il_factor* fact);
#endif
