#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

il_factor * il_factor_wrap_string(il_factor_string * self) {
	il_factor* ret = il_factor_new(ILFACTOR_STRING_T);
	ret->u.string_ = self;
	return ret;
}

il_factor_string * il_factor_string_new(string_view valuev) {
	il_factor_string* ret = (il_factor_string*)MEM_MALLOC(sizeof(il_factor_string));
	ret->valuev = valuev;
	return ret;
}

void il_factor_string_generate(il_factor_string * self, enviroment* env, call_context* cctx) {
	int index = enviroment_add_constant_string(env, self->valuev);
	opcode_buf_add(env->buf, (VectorItem)OP_SCONST);
	opcode_buf_add(env->buf, (VectorItem)index);
}

void il_factor_string_load(il_factor_string * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_string_eval(il_factor_string * self, enviroment * env, call_context* cctx) {
//	assert(TYPE_STRING->generic_self->core_type != NULL);
	return GENERIC_STRING;
}

char* il_factor_string_tostr(il_factor_string* self, enviroment* env) {
	return Strdup(Ref2Str(self->valuev));
}

void il_factor_string_delete(il_factor_string * self) {
	MEM_FREE(self);
}