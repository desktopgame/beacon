#ifndef BEACON_IL_ILFactor_call_op_H
#define BEACON_IL_ILFactor_call_op_H
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
typedef struct ILFactor_call_op {
	ILFactor* parent;
	ILFactor* receiver;
	//Vector* type_argument_list;
	Vector* argument_list;
	ilcall_type type;
	union {
		ILFactor_invoke* invoke_;
		ILFactor_invoke_static* invoke_static_;
		ILFactor_invoke_bound* invoke_bound_;
	} u;
} ILFactor_call_op;

ILFactor* WrapCallOp(ILFactor_call_op* self);

ILFactor_call_op* NewILCallOp();

void LoadCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);

char* ILCallOpToString(ILFactor_call_op* self, Enviroment* env);

void GenerateILCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);

void DeleteILCallOp(ILFactor_call_op* self);

#endif
