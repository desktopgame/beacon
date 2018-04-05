#ifndef BEACON_IL_il_factor_call_op_H
#define BEACON_IL_il_factor_call_op_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "invoke/il_factor_invoke_impl.h"
#include "invoke/il_factor_invoke_static_impl.h"
#include "invoke/il_factor_invoke_bound_impl.h"

#define IL_FACT2CALL(fact) (il_factor_cast_call_op(fact))

struct enviroment;
struct generic_type;

typedef enum ilcall_type {
	ilcall_type_invoke,
	ilcall_type_invoke_static,
	ilcall_type_invoke_bound,
	ilcall_type_undefined,
} ilcall_type;

typedef struct il_factor_call_op {
	il_factor* parent;
	il_factor* receiver;
	//vector* type_argument_list;
	vector* argument_list;
	ilcall_type type;
	union {
		il_factor_invoke* invoke_;
		il_factor_invoke_static* invoke_static_;
		il_factor_invoke_bound* invoke_bound_;
	} u;
} il_factor_call_op;

il_factor* il_factor_wrap_call_op(il_factor_call_op* self);

il_factor_call_op* il_factor_call_op_new();

void il_factor_call_op_dump(il_factor_call_op* self, int depth);

void il_factor_call_op_load(il_factor_call_op* self, struct enviroment* env, il_context* cache, il_ehandler* eh);

struct generic_type* il_factor_call_op_eval(il_factor_call_op* self, struct enviroment* env, il_context* cache);

void il_factor_call_op_generate(il_factor_call_op* self, struct enviroment* env, il_context* cache);

void il_factor_call_op_delete(il_factor_call_op* self);

il_factor_call_op* il_factor_cast_call_op(il_factor* fact);
#endif
