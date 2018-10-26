#ifndef BEACON_IL_il_factor_call_op_H
#define BEACON_IL_il_factor_call_op_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "invoke/il_factor_invoke_impl.h"
#include "invoke/il_factor_invoke_static_impl.h"
#include "invoke/il_factor_invoke_bound_impl.h"


struct Enviroment;
struct GenericType;
/**
 * 関数呼び出し演算子の種類を表す列挙型.
 */
typedef enum ilcall_type {
	ILCALL_TYPE_INVOKE_T,
	ILCALL_TYPE_INVOKE_STATIC_T,
	ILCALL_TYPE_INVOKE_BOUND_T,
	ILCALL_TYPE_UNDEFINED_T,
} ilcall_type;

/**
 * 関数呼び出し演算子を表す構造体.
 */
typedef struct il_factor_call_op {
	il_factor* parent;
	il_factor* receiver;
	//Vector* type_argument_list;
	Vector* argument_list;
	ilcall_type type;
	union {
		il_factor_invoke* invoke_;
		il_factor_invoke_static* invoke_static_;
		il_factor_invoke_bound* invoke_bound_;
	} u;
} il_factor_call_op;

il_factor* WrapCallOp(il_factor_call_op* self);

il_factor_call_op* NewILCallOp();

void LoadCallOp(il_factor_call_op* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILCallOp(il_factor_call_op* self, Enviroment* env, CallContext* cctx);

char* ILCallOpToString(il_factor_call_op* self, Enviroment* env);

void GenerateILCallOp(il_factor_call_op* self, Enviroment* env, CallContext* cctx);

void DeleteILCallOp(il_factor_call_op* self);

#endif
