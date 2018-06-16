#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../il_factor_interface.h"

il_factor_explicit_binary_op* il_factor_explicit_binary_op_new(operator_type type) {
	il_factor_explicit_binary_op* ret = (il_factor_explicit_binary_op*)MEM_MALLOC(sizeof(il_factor_explicit_binary_op));
	ret->type = type;
	ret->receiver = NULL;
	ret->arg = NULL;
	return ret;
}

void il_factor_explicit_binary_op_delete(il_factor_explicit_binary_op* self) {
	il_factor_delete(self->receiver);
	il_factor_delete(self->arg);
	MEM_FREE(self);
}