#include "il_factor_logic_op_impl.h"
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

il_factor_logic_op* il_factor_logic_op_new(operator_type type) {
	il_factor_logic_op* ret = (il_factor_logic_op*)MEM_MALLOC(sizeof(il_factor_logic_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_logic_op_dump(il_factor_logic_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_logic_op_eval(il_factor_logic_op* self, enviroment* env) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void il_factor_logic_op_generate(il_factor_logic_op* self, enviroment* env) {
	il_factor_generate(self->parent->right, env);
	il_factor_generate(self->parent->left, env);
	if(il_factor_binary_op_int_int(self->parent, env)) {
		opcode_buf_add(env->buf, operator_to_iopcode(self->type));
	} else if(il_factor_binary_op_double_double(self->parent, env)) {
		opcode_buf_add(env->buf, operator_to_dopcode(self->type));
	}
}

void il_factor_logic_op_load(il_factor_logic_op* self, enviroment* env) {
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
		case operator_bit_or: return op_ibit_or;
		case operator_bit_and: return op_ibit_and;
		case operator_logic_or: return op_ilogic_or;
		case operator_logic_and: return op_ilogic_and;
	}
	assert(false);
}

static opcode operator_to_dopcode(operator_type type) {
	assert(false);
}