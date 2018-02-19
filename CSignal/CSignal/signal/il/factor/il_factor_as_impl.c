#include "il_factor_as_impl.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <assert.h>

il_factor * il_factor_wrap_as(il_factor_as * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_as;
	ret->u.as_ = self;
	return ret;
}

il_factor_as * il_factor_as_new() {
	il_factor_as* ret = (il_factor_as*)MEM_MALLOC(sizeof(il_factor_as));
	ret->fact = NULL;
	ret->fqcn = fqcn_cache_new();
	return ret;
}

void il_factor_as_dump(il_factor_as * self, int depth) {
	text_putindent(depth);
	text_printf("as ");
	fqcn_cache_print(self->fqcn);
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_as_generate(il_factor_as * self, enviroment * env, il_load_cache* cache) {
	il_factor_generate(self->fact, env, cache);

	type* from = il_factor_eval(self->fact, env, cache);
	type* to = fqcn_type(self->fqcn, (namespace_*)vector_top(cache->namespace_vec));
	int dist = type_distance(to, from);
	assert(dist != -1);
	if (dist != -1) {
		opcode_buf_add(env->buf, op_lookup);
		opcode_buf_add(env->buf, to->absoluteIndex);
	}
}

void il_factor_as_load(il_factor_as * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
}

type * il_factor_as_eval(il_factor_as * self, enviroment * env, il_load_cache* cache) {
	namespace_* n = (namespace_*)vector_top(cache->namespace_vec);
	return fqcn_type(self->fqcn, n);
}

void il_factor_as_delete(il_factor_as * self) {
	fqcn_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
