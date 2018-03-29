#ifndef BEACON_IL_IL_FACTOR_OP_CALL_H
#define BEACON_IL_IL_FACTOR_OP_CALL_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"

struct enviroment;
struct generic_type;

typedef struct il_factor_op_call {
	il_factor* parent;
	il_factor* receiver;
	//vector* type_argument_list;
	vector* argument_list;
} il_factor_op_call;

il_factor* il_factor_wrap_op_call(il_factor_op_call* self);

il_factor_op_call* il_factor_op_call_new();

void il_factor_op_call_load(il_factor_op_call* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

struct generic_type* il_factor_op_call_eval(il_factor_op_call* self, struct enviroment* env, il_load_cache* cache);

void il_factor_op_call_generate(il_factor_op_call* self, struct enviroment* env, il_load_cache* cache);

void il_factor_op_call_delete(il_factor_op_call* self);
#endif
