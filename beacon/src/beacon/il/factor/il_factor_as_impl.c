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
	il_factor* ret = il_factor_new(ilfactor_as);
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
	il_factor_generate(self->fact, env);
}

void il_factor_as_load(il_factor_as * self, enviroment * env) {
	il_factor_load(self->fact, env);
}

generic_type* il_factor_as_eval(il_factor_as * self, enviroment * env) {
	namespace_* n = cctop_namespace();
	return import_manager_resolve(ccget_class_loader()->import_manager, n, self->fqcn);
}

void il_factor_as_delete(il_factor_as * self) {
	generic_cache_delete(self->fqcn);
	il_factor_delete(self->fact);
	MEM_FREE(self);
}

char* il_factor_as_tostr(il_factor_as* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* factstr = il_factor_tostr(self->fact, env);
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