#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../util/mem.h"

il_factor * il_factor_wrap_string(il_factor_string * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_string;
	ret->u.string_ = self;
	return ret;
}

il_factor_string * il_factor_string_new(string_view valuev) {
	il_factor_string* ret = (il_factor_string*)MEM_MALLOC(sizeof(il_factor_string));
	ret->valuev = valuev;
	return ret;
}

void il_factor_string_dump(il_factor_string * self, int depth) {
	text_putindent(depth);
	text_printf("String %s", string_pool_ref2str(self->valuev));
	text_putline();
}

void il_factor_string_generate(il_factor_string * self, enviroment* env) {
	int index = enviroment_add_constant_string(env, self->valuev);
	opcode_buf_add(env->buf, (vector_item)op_sconst);
	opcode_buf_add(env->buf, (vector_item)index);
}

void il_factor_string_load(il_factor_string * self, enviroment * env) {
}

generic_type* il_factor_string_eval(il_factor_string * self, enviroment * env) {
//	assert(TYPE_STRING->generic_self->core_type != NULL);
	return GENERIC_STRING;
}

char* il_factor_string_tostr(il_factor_string* self, enviroment* env) {
	return text_strdup(string_pool_ref2str(self->valuev));
}

void il_factor_string_delete(il_factor_string * self) {
	MEM_FREE(self);
}

il_factor_string* il_factor_cast_string(il_factor* fact) {
	assert(fact->type == ilfactor_string);
	return fact->u.string_;
}