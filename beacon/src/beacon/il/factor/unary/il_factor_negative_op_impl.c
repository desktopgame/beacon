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

il_factor_negative_op* MallocILNegativeOp(OperatorType type, const char* filename, int lineno) {
	il_factor_negative_op* ret = (il_factor_negative_op*)mem_malloc(sizeof(il_factor_negative_op), filename, lineno);
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILNegativeOp(il_factor_negative_op * self, Enviroment * env, call_context* cctx) {
	return EvalILFactor(self->parent->a, env, cctx);
}

void GenerateILNegativeOp(il_factor_negative_op* self, Enviroment* env, call_context* cctx) {
	generic_type* gt = EvalILFactor(self->parent->a, env, cctx);
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->a, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_INT) {
			AddOpcodeBuf(env->Bytecode, OP_INEG);
		} else if(GENERIC2TYPE(gt) == TYPE_DOUBLE) {
			AddOpcodeBuf(env->Bytecode, OP_DNEG);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->a, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILNegativeOp(il_factor_negative_op* self, Enviroment* env, call_context* cctx) {
	generic_type* gt = EvalILFactor(self->parent->a, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_INT &&
	   GENERIC2TYPE(gt) != TYPE_DOUBLE) {
		self->operator_index = GetIndexILUnaryOp(self->parent, env, cctx);
	}
}

void DeleteILNegativeOp(il_factor_negative_op* self) {
	MEM_FREE(self);
}

char* ILNegativeOpToString(il_factor_negative_op* self, Enviroment* env) {
	return ILUnaryOpToString_simple(self->parent, env);
}