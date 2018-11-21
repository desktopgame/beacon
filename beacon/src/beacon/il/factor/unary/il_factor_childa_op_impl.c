#include "il_factor_childa_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

ILChildaOp* NewILChildaOp(bc_OperatorType type) {
	ILChildaOp* ret = (ILChildaOp*)MEM_MALLOC(sizeof(ILChildaOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILChildaOp(ILChildaOp * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_GenericType* gtype = bc_EvalILFactor(self->Parent->Arg, env, cctx);
	if(self->OperatorIndex == -1) {
		//GenerateILFactor(self->Parent->Arg, env);
		if(bc_GENERIC2TYPE(gtype) == BC_TYPE_INT) {
			return bc_TYPE2GENERIC(BC_TYPE_INT);
		} else if(bc_GENERIC2TYPE(gtype) == BC_TYPE_BOOL) {
			return bc_TYPE2GENERIC(BC_TYPE_BOOL);
		} else {
			assert(false);
		}
	} else {
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		assert(self->OperatorIndex != -1);
		bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(gtype)), self->OperatorIndex);
		return ApplyILUnaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
	}
}

void GenerateILChildaOp(ILChildaOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		bc_GenericType* gtype = bc_EvalILFactor(self->Parent->Arg, env, cctx);
		if(bc_GENERIC2TYPE(gtype) == BC_TYPE_INT) {
			bc_AddOpcodeBuf(env->Bytecode, OP_IFLIP);
		} else if(bc_GENERIC2TYPE(gtype) == BC_TYPE_BOOL) {
			bc_AddOpcodeBuf(env->Bytecode, OP_BFLIP);
		} else {
			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILChildaOp(ILChildaOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gtype = bc_EvalILFactor(self->Parent->Arg, env, cctx);
	if(bc_GENERIC2TYPE(gtype) != BC_TYPE_INT &&
	   bc_GENERIC2TYPE(gtype) != BC_TYPE_BOOL) {
		self->OperatorIndex = GetIndexILUnaryOp(self->Parent, env, cctx);
	}
}

void DeleteILChildaOp(ILChildaOp* self) {
	MEM_FREE(self);
}

char* ILChildaOpToString(ILChildaOp* self, bc_Enviroment* env) {
	return ILUnaryOpToString_simple(self->Parent, env);
}