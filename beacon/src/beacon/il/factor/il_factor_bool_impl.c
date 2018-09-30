#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

il_factor * WrapILBool(il_factor_bool * self) {
	il_factor* ret = il_factor_new(ILFACTOR_BOOL_T);
	ret->u.bool_ = self;
	return ret;
}

il_factor_bool * NewILBool(bool b) {
	il_factor_bool* ret = (il_factor_bool*)MEM_MALLOC(sizeof(il_factor_bool));
	ret->a = b;
	return ret;
}

void il_factor_bool_generate(il_factor_bool * self, enviroment * env, call_context* cctx) {
	if (self->a) {
		AddOpcodeBuf(env->buf, OP_TRUE);
	} else {
		AddOpcodeBuf(env->buf, OP_FALSE);
	}
}

generic_type* EvalILBool(il_factor_bool * self, enviroment * env, call_context* cctx) {
	return GENERIC_BOOL;
}

char* ILBoolToString(il_factor_bool* self, enviroment* env) {
	return Strdup(self->a ? "true" : "false");
}

void DeleteILBool(il_factor_bool * self) {
	MEM_FREE(self);
}