#include "il_factor_explicit_unary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../vm/enviroment.h"
#include "../il_factor_interface.h"

il_factor* il_factor_wrap_explicit_unary_op(il_factor_explicit_unary_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_explicit_unary_op;
	ret->u.exp_unary_op = self;
	return ret;
}

il_factor_explicit_unary_op* il_factor_explicit_unary_op_new(operator_type type) {
	il_factor_explicit_unary_op* ret = (il_factor_explicit_unary_op*)MEM_MALLOC(sizeof(il_factor_explicit_unary_op));
	ret->type = type;
	ret->receiver = NULL;
	return ret;
}

void il_factor_explicit_unary_op_dump(il_factor_explicit_unary_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
}

void il_factor_explicit_unary_op_generate(il_factor_explicit_unary_op* self, enviroment* env) {
}

void il_factor_explicit_unary_op_load(il_factor_explicit_unary_op* self, enviroment* env) {
}

generic_type* il_factor_explicit_unary_op_eval(il_factor_explicit_unary_op* self, enviroment* env) {
	return NULL;
}

void il_factor_explicit_unary_op_delete(il_factor_explicit_unary_op* self) {
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}