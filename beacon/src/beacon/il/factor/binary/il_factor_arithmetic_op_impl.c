#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_interface.h"

il_factor_arithmetic_op* il_factor_arithmetic_op_new(operator_type type) {
	il_factor_arithmetic_op* ret = (il_factor_arithmetic_op*)MEM_MALLOC(sizeof(il_factor_arithmetic_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_arithmetic_op_dump(il_factor_arithmetic_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_arithmetic_op_eval(il_factor_arithmetic_op * self, enviroment * env) {
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

void il_factor_arithmetic_op_generate(il_factor_arithmetic_op* self, enviroment* env) {
}

void il_factor_arithmetic_op_load(il_factor_arithmetic_op* self, enviroment* env) {
}

void il_factor_arithmetic_op_delete(il_factor_arithmetic_op* self) {
	MEM_FREE(self);
}

char* il_factor_arithmetic_op_tostr(il_factor_arithmetic_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}
//static