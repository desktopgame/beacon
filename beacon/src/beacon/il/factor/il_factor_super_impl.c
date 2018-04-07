#include "il_factor_super_impl.h"
#include <stdio.h>
#include <assert.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"

il_factor_super* il_factor_super_new() {
	il_factor_super* ret = (il_factor_super*)MEM_MALLOC(sizeof(il_factor_super));
	ret->resolved = NULL;
	return ret;
}

void il_factor_super_dump(il_factor_super * self, int depth) {
	text_putindent(depth);
	text_printf("super");
	text_putline();
}

void il_factor_super_generate(il_factor_super * self, enviroment * env, il_context* ilctx) {
	opcode_buf_add(env->buf, op_super);
}

void il_factor_super_load(il_factor_super * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
}

generic_type* il_factor_super_eval(il_factor_super * self, enviroment * env, il_context* ilctx) {
	if(self->resolved == NULL) {
		type* t = ((type*)vector_top(ilctx->type_vec));
		assert(t->tag == type_class);
		self->resolved = generic_type_new(t->u.class_->super_class->core_type->u.class_->parent);
	}
	return self->resolved;
}

void il_factor_super_delete(il_factor_super * self) {
	generic_type_delete(self->resolved);
	MEM_FREE(self);
}
