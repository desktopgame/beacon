#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"

il_factor_arithmetic_op* il_factor_arithmetic_op_new(operator_type type) {
	il_factor_arithmetic_op* ret = (il_factor_arithmetic_op*)MEM_MALLOC(sizeof(il_factor_arithmetic_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_arithmetic_op_dump(il_factor_arithmetic_op* self, int depth) {
}

generic_type* il_factor_arithmetic_op_eval(il_factor_arithmetic_op * self, enviroment * env) {
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
	return NULL;
}