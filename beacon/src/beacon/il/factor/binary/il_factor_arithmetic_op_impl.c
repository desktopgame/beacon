#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"

il_factor_arithmeric_op* il_factor_arithmeric_op_new(operator_type type) {
	il_factor_arithmeric_op* ret = (il_factor_arithmeric_op*)MEM_MALLOC(sizeof(il_factor_arithmeric_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_arithmeric_op_delete(il_factor_arithmeric_op* self) {
	MEM_FREE(self);
}