#include "il_factor_cast_impl.h"
#include "../../env/fqcn_cache.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../util/vector.h"
#include "../../env/namespace.h"
#include <stdio.h>

il_factor * il_factor_wrap_cast(il_factor_cast * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_cast;
	ret->u.cast_ = self;
	return ret;
}

il_factor_cast * il_factor_cast_new(il_factor * fact) {
	il_factor_cast* ret = (il_factor_cast*)MEM_MALLOC(sizeof(il_factor_cast));
	ret->fqcn = fqcn_cache_new();
	ret->fact = fact;
	return ret;
}

void il_factor_cast_dump(il_factor_cast * self, int depth) {
	text_putindent(depth);
	printf("cast");
	text_putline();
	fqcn_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_cast_generate(il_factor_cast * self, enviroment * env) {
	il_factor_generate(self->fact, env);
	type* t = fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec));
	opcode_buf_add(env->buf, op_lookup);
	opcode_buf_add(env->buf, t->absoluteIndex);
}

void il_factor_cast_load(il_factor_cast * self, enviroment * env, il_ehandler * eh) {
}

type * il_factor_cast_eval(il_factor_cast * self, enviroment * env) {
	return fqcn_type(self->fqcn, (namespace_*)vector_top(env->namespace_vec));
}

void il_factor_cast_delete(il_factor_cast * self) {
	fqcn_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
