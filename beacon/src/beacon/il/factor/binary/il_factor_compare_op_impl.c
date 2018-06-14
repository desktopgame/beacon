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
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_compare_op_eval(il_factor_compare_op * self, enviroment * env) {
	generic_type* ret = TYPE2GENERIC(TYPE_BOOL);
	assert(ret != NULL);
	return ret;
}

void il_factor_compare_op_generate(il_factor_compare_op* self, enviroment* env) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env);
		il_factor_generate(self->parent->left, env);
		if(il_factor_binary_op_int_int(self->parent, env)) {
			opcode_buf_add(env->buf, operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_double_double(self->parent, env)) {
			opcode_buf_add(env->buf, operator_to_dopcode(self->type));
		} else if(il_factor_binary_op_char_char(self->parent, env)) {
			opcode_buf_add(env->buf, operator_to_copcode(self->type));
		} else {
			il_error_report(ilerror_undefined_operator, operator_tostring(self->type));
//			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env);
		il_factor_generate(self->parent->left, env);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_compare_op_load(il_factor_compare_op* self, enviroment* env) {
	self->operator_index = il_factor_binary_op_index(self->parent, env);
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
		case operator_gt: return op_igt;
		case operator_ge: return op_ige;
		case operator_lt: return op_ilt;
		case operator_le: return op_ile;
		case operator_eq: return op_ieq;
		case operator_noteq: return op_inoteq;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	switch(type) {
		case operator_gt: return op_dgt;
		case operator_ge: return op_dge;
		case operator_lt: return op_dlt;
		case operator_le: return op_dle;
		case operator_eq: return op_deq;
		case operator_noteq: return op_dnoteq;
	}
	assert(false);
}
static opcode operator_to_copcode(operator_type type) {
	switch(type) {
		case operator_gt: return op_cgt;
		case operator_ge: return op_cge;
		case operator_lt: return op_clt;
		case operator_le: return op_cle;
		case operator_eq: return op_ceq;
		case operator_noteq: return op_cnoteq;
	}
	assert(false);
}