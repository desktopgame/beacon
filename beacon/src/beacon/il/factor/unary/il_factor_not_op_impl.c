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

il_factor_not_op* NewILNotOp(operator_type type) {
	il_factor_not_op* ret = (il_factor_not_op*)MEM_MALLOC(sizeof(il_factor_not_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILNotOp(il_factor_not_op * self, enviroment * env, call_context* cctx) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void il_factor_not_op_generate(il_factor_not_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->a, env, cctx);
		if(GetLastBCError()) {
			return;
		}
		generic_type* gt = EvalILFactor(self->parent->a, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_BOOL) {
			AddOpcodeBuf(env->buf, OP_BNOT);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->a, env, cctx);
		AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->buf, self->operator_index);
	}
}

void LoadILNotOp(il_factor_not_op* self, enviroment* env, call_context* cctx) {
	 LoadILFactor(self->parent->a, env, cctx);
	generic_type* gt = EvalILFactor(self->parent->a, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_BOOL) {
		self->operator_index = il_factor_unary_op_index(self->parent, env, cctx);
	}
}

void DeleteILNotOp(il_factor_not_op* self) {
	MEM_FREE(self);
}

char* ILNotOpToString(il_factor_not_op* self, enviroment* env) {
	return ILUnaryOpToString_simple(self->parent, env);
}