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

il_factor_shift_op* il_factor_shift_op_new(operator_type type) {
	il_factor_shift_op* ret = (il_factor_shift_op*)MEM_MALLOC(sizeof(il_factor_shift_op));
	ret->parent = NULL;
	ret->type = type;
	ret->operator_index = -1;
	return ret;
}

generic_type* il_factor_shift_op_eval(il_factor_shift_op * self, enviroment * env, call_context* cctx) {
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
	return il_factor_binary_op_apply(self->parent, operator_ov->return_gtype, env, cctx);
}

void il_factor_shift_op_generate(il_factor_shift_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
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

void il_factor_shift_OP_LOAD(il_factor_shift_op* self, enviroment* env, call_context* cctx) {
	if(!il_factor_binary_op_int_int(self->parent, env, cctx)) {
		self->operator_index = il_factor_binary_op_index(self->parent, env, cctx);
	}
}

void il_factor_shift_op_delete(il_factor_shift_op* self) {
	MEM_FREE(self);
}

char* il_factor_shift_op_tostr(il_factor_shift_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
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