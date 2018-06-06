#include "il_factor_logic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_interface.h"

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
}

void il_factor_logic_op_load(il_factor_logic_op* self, enviroment* env) {
}

void il_factor_logic_op_delete(il_factor_logic_op* self) {
	MEM_FREE(self);
}

char* il_factor_logic_op_tostr(il_factor_logic_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}