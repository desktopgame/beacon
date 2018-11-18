#include "il_factor_negative_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

ILNegativeOp* MallocILNegativeOp(bc_OperatorType type, const char* filename, int lineno) {
	ILNegativeOp* ret = (ILNegativeOp*)bc_MXMalloc(sizeof(ILNegativeOp), filename, lineno);
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

GenericType* EvalILNegativeOp(ILNegativeOp * self, Enviroment * env, CallContext* cctx) {
	return EvalILFactor(self->Parent->Arg, env, cctx);
}

void GenerateILNegativeOp(ILNegativeOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->Parent->Arg, env, cctx);
	if(self->OperatorIndex == -1) {
		GenerateILFactor(self->Parent->Arg, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_INT) {
			AddOpcodeBuf(env->Bytecode, OP_INEG);
		} else if(GENERIC2TYPE(gt) == TYPE_DOUBLE) {
			AddOpcodeBuf(env->Bytecode, OP_DNEG);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->Parent->Arg, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILNegativeOp(ILNegativeOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->Parent->Arg, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_INT &&
	   GENERIC2TYPE(gt) != TYPE_DOUBLE) {
		self->OperatorIndex = GetIndexILUnaryOp(self->Parent, env, cctx);
	}
}

void DeleteILNegativeOp(ILNegativeOp* self) {
	MEM_FREE(self);
}

char* ILNegativeOpToString(ILNegativeOp* self, Enviroment* env) {
	return ILUnaryOpToString_simple(self->Parent, env);
}