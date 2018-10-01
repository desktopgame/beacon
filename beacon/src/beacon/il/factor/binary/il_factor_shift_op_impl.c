#include "il_factor_shift_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_dopcode(operator_type type);

il_factor_shift_op* NewILShiftOp(operator_type type) {
	il_factor_shift_op* ret = (il_factor_shift_op*)MEM_MALLOC(sizeof(il_factor_shift_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILShiftOp(il_factor_shift_op * self, enviroment * env, call_context* cctx) {
	generic_type* lgtype = EvalILFactor(self->parent->left, env, cctx);
	generic_type* rgtype = EvalILFactor(self->parent->right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	type* cint = TYPE_INT;
	type* cdouble = TYPE_DOUBLE;
	if(GENERIC2TYPE(lgtype) == cint &&
	   GENERIC2TYPE(rgtype) == cint) {
		return TYPE2GENERIC(cint);
	}
	if(GENERIC2TYPE(lgtype) == cint &&
	   GENERIC2TYPE(rgtype) == cint) {
		return TYPE2GENERIC(cdouble);
	}
	if(self->operator_index == -1) {
		ThrowBCError(
			BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
			operator_tostring(self->type)
		);
		return NULL;
	}
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return ApplyILBinaryOp(self->parent, operator_ov->return_gtype, env, cctx);
}

void GenerateILShiftOp(il_factor_shift_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->buf, (VectorItem)operator_to_iopcode(self->type));
		} else {
			ThrowBCError(
				BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
				operator_tostring(self->type)
			);
		}
	} else {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->buf, self->operator_index);
	}
}

void LoadILShiftOp(il_factor_shift_op* self, enviroment* env, call_context* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx)) {
		self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILShiftOp(il_factor_shift_op* self) {
	MEM_FREE(self);
}

char* ILShiftOpToString(il_factor_shift_op* self, enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case OPERATOR_LSHIFT_T: return OP_ILSH;
		case OPERATOR_RSHIFT_T: return OP_IRSH;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	assert(false);
}