#include "il_factor_cast_impl.h"
#include "../../env/fqcn_cache.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../util/vector.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include "../../env/generic_cache.h"

il_factor * il_factor_wrap_cast(il_factor_cast * self) {
	il_factor* ret = il_factor_new(ilfactor_cast_T);
	ret->u.cast_ = self;
	return ret;
}

il_factor_cast * il_factor_cast_new(il_factor * fact) {
	il_factor_cast* ret = (il_factor_cast*)MEM_MALLOC(sizeof(il_factor_cast));
	ret->fqcn = generic_cache_new();
	ret->fact = fact;
	return ret;
}

void il_factor_cast_dump(il_factor_cast * self, int depth) {
	io_printi(depth);
	printf("cast");
	io_println();
	generic_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_cast_ge_Tnerate(il_factor_cast * self, enviroment * env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
}

void il_factor_cast_load(il_factor_cast * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_cast_eval(il_factor_cast * self, enviroment * env, call_context* cctx) {
	return import_manager_resolve(NULL, NULL, self->fqcn, cctx);
}

char* il_factor_cast_tostr(il_factor_cast* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* name = generic_cache_tostr(self->fqcn);
	char* fact = il_factor_tostr(self->fact, env);
	string_buffer_append(sb, '(');
	string_buffer_appends(sb, name);
	string_buffer_append(sb, ')');
	string_buffer_appends(sb, fact);
	MEM_FREE(name);
	MEM_FREE(fact);
	return string_buffer_release(sb);
}

void il_factor_cast_delete(il_factor_cast * self) {
	generic_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}

il_factor_cast* il_factor_cast_cast_T(il_factor* fact) {
	assert(fact->type == ilfactor_cast_T);
	return fact->u.cast_;
}