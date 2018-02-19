#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"

il_factor * il_factor_wrap_bool(il_factor_bool * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_bool;
	ret->u.bool_ = self;
	return ret;
}

il_factor_bool * il_factor_bool_new(bool b) {
	il_factor_bool* ret = (il_factor_bool*)MEM_MALLOC(sizeof(il_factor_bool));
	ret->a = b;
	return ret;
}

void il_factor_bool_dump(il_factor_bool * self, int depth) {
	text_putindent(depth);
	text_putb(self->a);
	text_putline();
}

void il_factor_bool_generate(il_factor_bool * self, enviroment * env, il_load_cache* cache) {
	if (self->a) {
		opcode_buf_add(env->buf, op_true);
	} else {
		opcode_buf_add(env->buf, op_false);
	}
}

type * il_factor_bool_eval(il_factor_bool * self, enviroment * env, il_load_cache* cache) {
	return CL_BOOL;
}

void il_factor_bool_delete(il_factor_bool * self) {
	MEM_FREE(self);
}
