#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"
#include <assert.h>

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_dopcode(operator_type type);

il_factor_arithmetic_op* il_factor_arithmetic_op_new(operator_type type) {
	il_factor_arithmetic_op* ret = (il_factor_arithmetic_op*)MEM_MALLOC(sizeof(il_factor_arithmetic_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

void il_factor_arithmetic_op_dump(il_factor_arithmetic_op* self, int depth) {
	io_printi(depth);
	operator_fprintf(stdout, self->type);
	io_println();
}

generic_type* il_factor_arithmetic_op_eval(il_factor_arithmetic_op * self, enviroment * env, call_context* cctx) {
	generic_type* lgtype = il_factor_eval(self->parent->left, env, cctx);
	generic_type* rgtype = il_factor_eval(self->parent->right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	type* cint = TYPE_INT;
	type* cdouble = TYPE_DOUBLE;
	if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
		return TYPE2GENERIC(cint);
	}
	if(il_factor_binary_op_double_double(self->parent, env, cctx)) {
		return TYPE2GENERIC(cdouble);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->operator_index == -1) {
		bc_error_throw(bcerror_undefined_compare_operator_T,
			operator_tostring(self->type)
		);
		return NULL;
	}
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return il_factor_binary_op_apply(self->parent, operator_ov->return_gtype, env, cctx);
}

void il_factor_arithmetic_op_generate(il_factor_arithmetic_op* self, enviroment* env, call_context* cctx) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_double_double(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_dopcode(self->type));
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_arithmetic_op_load(il_factor_arithmetic_op* self, enviroment* env, call_context* cctx) {
	if(!il_factor_binary_op_int_int(self->parent, env, cctx) &&
	   !il_factor_binary_op_double_double(self->parent, env, cctx)) {
		self->operator_index = il_factor_binary_op_index(self->parent, env, cctx);
	}
}

void il_factor_arithmetic_op_delete(il_factor_arithmetic_op* self) {
	MEM_FREE(self);
}

char* il_factor_arithmetic_op_tostr(il_factor_arithmetic_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case operator_add_T: return op_iadd;
		case operator_sub_T: return op_isub;
		case operator_mul_T: return op_imul;
		case operator_div_T: return op_idiv;
		case operator_mod_T: return op_imod;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	switch(type) {
		case operator_add_T: return op_dadd;
		case operator_sub_T: return op_dsub;
		case operator_mul_T: return op_dmul;
		case operator_div_T: return op_ddiv;
		case operator_mod_T: return op_dmod;
	}
	assert(false);
}