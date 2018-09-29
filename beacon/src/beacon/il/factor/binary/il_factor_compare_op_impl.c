#include "il_factor_compare_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/type_interface.h"

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_dopcode(operator_type type);
static opcode operator_to_copcode(operator_type type);

il_factor_compare_op* il_factor_compare_op_new(operator_type type) {
	il_factor_compare_op* ret = (il_factor_compare_op*)MEM_MALLOC(sizeof(il_factor_compare_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* il_factor_compare_op_eval(il_factor_compare_op * self, enviroment * env, call_context* cctx) {
	generic_type* ret = TYPE2GENERIC(TYPE_BOOL);
	assert(ret != NULL);
	return ret;
}

void il_factor_compare_op_generate(il_factor_compare_op* self, enviroment* env, call_context* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (VectorItem)operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_double_double(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (VectorItem)operator_to_dopcode(self->type));
		} else if(il_factor_binary_op_char_char(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (VectorItem)operator_to_copcode(self->type));
		} else {
			bc_error_throw(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
				operator_tostring(self->type)
			);
//			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		opcode_buf_add(env->buf, OP_INVOKEOPERATOR);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_compare_OP_LOAD(il_factor_compare_op* self, enviroment* env, call_context* cctx) {
	if(!il_factor_binary_op_int_int(self->parent, env, cctx) &&
	   !il_factor_binary_op_double_double(self->parent, env, cctx) &&
	   !il_factor_binary_op_char_char(self->parent, env, cctx)) {
	self->operator_index = il_factor_binary_op_index(self->parent, env, cctx);
	}
}

void il_factor_compare_op_delete(il_factor_compare_op* self) {
	MEM_FREE(self);
}

char* il_factor_compare_op_tostr(il_factor_compare_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_IGT;
		case OPERATOR_GE_T: return OP_IGE;
		case OPERATOR_LT_T: return OP_ILT;
		case OPERATOR_LE_T: return OP_ILE;
		case OPERATOR_EQ_T: return OP_IEQ;
		case OPERATOR_NOT_EQ_T: return OP_INOTEQ;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_DGT;
		case OPERATOR_GE_T: return OP_DGE;
		case OPERATOR_LT_T: return OP_DLT;
		case OPERATOR_LE_T: return OP_DLE;
		case OPERATOR_EQ_T: return OP_DEQ;
		case OPERATOR_NOT_EQ_T: return OP_DNOTEQ;
	}
	assert(false);
}
static opcode operator_to_copcode(operator_type type) {
	switch(type) {
		case OPERATOR_GT_T: return OP_CGT;
		case OPERATOR_GE_T: return OP_CGE;
		case OPERATOR_LT_T: return OP_CLT;
		case OPERATOR_LE_T: return OP_CLE;
		case OPERATOR_EQ_T: return OP_CEQ;
		case OPERATOR_NOT_EQ_T: return OP_CNOTEQ;
	}
	assert(false);
}