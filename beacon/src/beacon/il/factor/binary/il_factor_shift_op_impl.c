#include "il_factor_shift_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_interface.h"

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_dopcode(operator_type type);

il_factor_shift_op* il_factor_shift_op_new(operator_type type) {
	il_factor_shift_op* ret = (il_factor_shift_op*)MEM_MALLOC(sizeof(il_factor_shift_op));
	ret->parent = NULL;
	ret->type = type;
	return ret;
}

void il_factor_shift_op_dump(il_factor_shift_op* self, int depth) {
}

generic_type* il_factor_shift_op_eval(il_factor_shift_op * self, enviroment * env) {
	generic_type* lgtype = il_factor_eval(self->parent->left, env);
	generic_type* rgtype = il_factor_eval(self->parent->right, env);
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
	return NULL;
}

void il_factor_shift_op_generate(il_factor_shift_op* self, enviroment* env) {
	il_factor_generate(self->parent->left, env);
	il_factor_generate(self->parent->right, env);
	if(il_factor_binary_op_int_int(self->parent, env)) {
		opcode_buf_add(env->buf, operator_to_iopcode(self->type));
	} else if(il_factor_binary_op_double_double(self->parent, env)) {
		opcode_buf_add(env->buf, operator_to_dopcode(self->type));
	}
}

void il_factor_shift_op_load(il_factor_shift_op* self, enviroment* env) {
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
		case operator_lshift: return op_ilsh;
		case operator_rshift: return op_irsh;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	assert(false);
}