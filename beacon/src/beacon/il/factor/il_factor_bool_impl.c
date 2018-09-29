#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

il_factor * il_factor_wrap_bool(il_factor_bool * self) {
	il_factor* ret = il_factor_new(ILFACTOR_BOOL_T);
	ret->u.bool_ = self;
	return ret;
}

il_factor_bool * il_factor_bool_new(bool b) {
	il_factor_bool* ret = (il_factor_bool*)MEM_MALLOC(sizeof(il_factor_bool));
	ret->a = b;
	return ret;
}

void il_factor_bool_generate(il_factor_bool * self, enviroment * env, call_context* cctx) {
	if (self->a) {
		opcode_buf_add(env->buf, OP_TRUE);
	} else {
		opcode_buf_add(env->buf, OP_FALSE);
	}
}

generic_type* il_factor_bool_eval(il_factor_bool * self, enviroment * env, call_context* cctx) {
	return GENERIC_BOOL;
}

char* il_factor_bool_tostr(il_factor_bool* self, enviroment* env) {
	return Strdup(self->a ? "true" : "false");
}

void il_factor_bool_delete(il_factor_bool * self) {
	MEM_FREE(self);
}