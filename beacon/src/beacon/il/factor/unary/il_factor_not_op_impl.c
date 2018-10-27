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

ILFactor_not_op* NewILNotOp(OperatorType type) {
	ILFactor_not_op* ret = (ILFactor_not_op*)MEM_MALLOC(sizeof(ILFactor_not_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

GenericType* EvalILNotOp(ILFactor_not_op * self, Enviroment * env, CallContext* cctx) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void GenerateILNotOp(ILFactor_not_op* self, Enviroment* env, CallContext* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->a, env, cctx);
		if(GetLastBCError()) {
			return;
		}
		GenericType* gt = EvalILFactor(self->parent->a, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_BOOL) {
			AddOpcodeBuf(env->Bytecode, OP_BNOT);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->a, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILNotOp(ILFactor_not_op* self, Enviroment* env, CallContext* cctx) {
	 LoadILFactor(self->parent->a, env, cctx);
	GenericType* gt = EvalILFactor(self->parent->a, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_BOOL) {
		self->operator_index = GetIndexILUnaryOp(self->parent, env, cctx);
	}
}

void DeleteILNotOp(ILFactor_not_op* self) {
	MEM_FREE(self);
}

char* ILNotOpToString(ILFactor_not_op* self, Enviroment* env) {
	return ILUnaryOpToString_simple(self->parent, env);
}