#include "il_factor_not_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

bc_ILNotOp* bc_NewILNotOp(bc_OperatorType type) {
	bc_ILNotOp* ret = (bc_ILNotOp*)MEM_MALLOC(sizeof(bc_ILNotOp));
	ret->Parent = NULL;
	ret->Type = type;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* bc_EvalILNotOp(bc_ILNotOp * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return bc_TYPE2GENERIC(BC_TYPE_BOOL);
}

void bc_GenerateILNotOp(bc_ILNotOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		if(bc_GetLastPanic()) {
			return;
		}
		bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
		if(bc_GENERIC2TYPE(gt) == BC_TYPE_BOOL) {
			bc_AddOpcodeBuf(env->Bytecode, OP_BNOT);
		} else {
			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void bc_LoadILNotOp(bc_ILNotOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	 bc_LoadILFactor(self->Parent->Arg, env, cctx);
	bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
	if(bc_GENERIC2TYPE(gt) != BC_TYPE_BOOL) {
		self->OperatorIndex = bc_GetIndexILUnaryOp(self->Parent, env, cctx);
	}
}

void bc_DeleteILNotOp(bc_ILNotOp* self) {
	MEM_FREE(self);
}

char* bc_ILNotOpToString(bc_ILNotOp* self, bc_Enviroment* env) {
	return bc_ILUnaryOpToStringSimple(self->Parent, env);
}