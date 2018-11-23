//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_call_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_ILCallOp_H
#define BEACON_IL_ILCallOp_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "invoke/il_factor_invoke_impl.h"
#include "invoke/il_factor_invoke_static_impl.h"
#include "invoke/il_factor_invoke_bound_impl.h"


struct bc_Enviroment;
struct bc_GenericType;
/**
 * 関数呼び出し演算子の種類を表す列挙型.
 */
typedef enum bc_ILCallType {
	ILCALL_TYPE_INVOKE_T,
	ILCALL_TYPE_INVOKE_STATIC_T,
	ILCALL_TYPE_INVOKE_BOUND_T,
	ILCALL_TYPE_UNDEFINED_T,
} bc_ILCallType;

/**
 * 関数呼び出し演算子を表す構造体.
 */
typedef struct bc_ILCallOp {
	bc_ILFactor* Parent;
	bc_ILFactor* Receiver;
	//Vector* type_argument_list;
	bc_Vector* Arguments;
	bc_ILCallType Type;
	union {
		ILInvoke* Invoke;
		ILInvokeStatic* InvokeStatic;
		ILInvokeBound* InvokeBound;
	} Kind;
} bc_ILCallOp;

bc_ILFactor* bc_WrapCallOp(bc_ILCallOp* self);

bc_ILCallOp* bc_NewILCallOp();

void bc_LoadCallOp(bc_ILCallOp* self, bc_Enviroment* env, bc_CallContext* cctx);

struct bc_GenericType* bc_EvalILCallOp(bc_ILCallOp* self, bc_Enviroment* env, bc_CallContext* cctx);

char* bc_ILCallOpToString(bc_ILCallOp* self, bc_Enviroment* env);

void bc_GenerateILCallOp(bc_ILCallOp* self, bc_Enviroment* env, bc_CallContext* cctx);

void bc_DeleteILCallOp(bc_ILCallOp* self);

#endif
