#include "il_factor_as_impl.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
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
	ret->fqcn = generic_cache_new();
	return ret;
}

void il_factor_as_dump(il_factor_as * self, int depth) {
	text_putindent(depth);
	text_printf("as ");
	generic_cache_print(self->fqcn);
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_as_generate(il_factor_as * self, enviroment * env) {
	il_factor_generate(self->fact, env, ilctx);
/*
	generic_type* from = il_factor_eval(self->fact, env, ilctx);
	generic_type* to = generic_cache_gtype(self->fqcn, (namespace_*)vector_top(ilctx->namespace_vec), ilctx);
//	int dist = type_distance(to, from);
//	assert(dist != -1);
	if (to->virtual_type_index != -1) {
//		opcode_buf_add(env->buf, op_glookup);
//		opcode_buf_add(env->buf, to->virtual_type_index);
		return;
	}
	bool cast = generic_type_castable(from, to);
	assert(cast);
	if (cast) {
//		opcode_buf_add(env->buf, op_lookup);
//		opcode_buf_add(env->buf, to->core_type->absolute_index);
	}
	*/
}

void il_factor_as_load(il_factor_as * self, enviroment * env) {
	il_factor_load(self->fact, env, ilctx);
}

generic_type* il_factor_as_eval(il_factor_as * self, enviroment * env) {
	namespace_* n = (namespace_*)vector_top(ilctx->namespace_vec);
	//return generic_cache_gtype(self->fqcn, n, ilctx);
	return import_manager_resolve(ilctx->class_loader_ref->import_manager, n, self->fqcn, ilctx);
}

void il_factor_as_delete(il_factor_as * self) {
	generic_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}

char* il_factor_as_tostr(il_factor_as* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* factstr = il_factor_tostr(self->fact, env, ilctx);
	char* to = generic_cache_tostr(self->fqcn);
	string_buffer_appendf(sb, "%s as %s", factstr, to);
	MEM_FREE(factstr);
	MEM_FREE(to);
	return string_buffer_release(sb);
}

il_factor_as* il_factor_cast_as(il_factor* fact) {
	assert(fact->type == ilfactor_as);
	return fact->u.as_;
}