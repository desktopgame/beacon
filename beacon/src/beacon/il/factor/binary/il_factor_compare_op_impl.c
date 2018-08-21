#include "il_factor_compare_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"
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

void il_factor_compare_op_dump(il_factor_compare_op* self, int depth) {
	io_printi(depth);
	operator_fprintf(stdout, self->type);
	io_println();
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
			opcode_buf_add(env->buf, (vector_item)operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_double_double(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_dopcode(self->type));
		} else if(il_factor_binary_op_char_char(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_copcode(self->type));
		} else {
			bc_error_throw(bcerror_undefined_compare_operator_T,
				operator_tostring(self->type)
			);
//			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_compare_op_load(il_factor_compare_op* self, enviroment* env, call_context* cctx) {
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
		case operator_gt_T: return op_igt;
		case operator_ge_T: return op_ige;
		case operator_lt_T: return op_ilt;
		case operator_le_T: return op_ile;
		case operator_eq_T: return op_ieq;
		case operator_not_Teq_T: return op_inoteq;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	switch(type) {
		case operator_gt_T: return op_dgt;
		case operator_ge_T: return op_dge;
		case operator_lt_T: return op_dlt;
		case operator_le_T: return op_dle;
		case operator_eq_T: return op_deq;
		case operator_not_Teq_T: return op_dnoteq;
	}
	assert(false);
}
static opcode operator_to_copcode(operator_type type) {
	switch(type) {
		case operator_gt_T: return op_cgt;
		case operator_ge_T: return op_cge;
		case operator_lt_T: return op_clt;
		case operator_le_T: return op_cle;
		case operator_eq_T: return op_ceq;
		case operator_not_Teq_T: return op_cnoteq;
	}
	assert(false);
}