#include "il_factor_logic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_bopcode(operator_type type);

il_factor_logic_op* il_factor_logic_op_new(operator_type type) {
	il_factor_logic_op* ret = (il_factor_logic_op*)MEM_MALLOC(sizeof(il_factor_logic_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* il_factor_logic_op_eval(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_INT);
	} else if(il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_BOOL);
	} else {
		generic_type* lgtype = il_factor_eval(self->parent->left, env, cctx);
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		if(self->operator_index == -1) {
			ThrowBCError(
				BCERROR_UNDEFINED_LOGIC_OPERATOR_T,
				operator_tostring(self->type)
			);
			return NULL;
		}
		operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
		return il_factor_binary_op_apply(self->parent, operator_ov->return_gtype, env, cctx);
	}
}

void il_factor_logic_op_generate(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
			AddOpcodeBuf(env->buf, (VectorItem)operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
			AddOpcodeBuf(env->buf, (VectorItem)operator_to_bopcode(self->type));
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		AddOpcodeBuf(env->buf, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->buf, self->operator_index);
	}
}

void il_factor_logic_OP_LOAD(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(!il_factor_binary_op_int_int(self->parent, env, cctx) &&
	   !il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
	self->operator_index = il_factor_binary_op_index(self->parent, env, cctx);
	}
}

void il_factor_logic_op_delete(il_factor_logic_op* self) {
	MEM_FREE(self);
}

char* il_factor_logic_op_tostr(il_factor_logic_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_IBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_IBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_ILOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_ILOGIC_AND;
	}
	assert(false);
}

static opcode operator_to_bopcode(operator_type type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_BBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_BBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_BLOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_BLOGIC_AND;
	}
	assert(false);
}