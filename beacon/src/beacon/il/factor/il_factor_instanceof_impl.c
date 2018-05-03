#include "il_factor_instanceof_impl.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/import_manager.h"
#include "../../env/class_loader.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_factor* il_factor_wrap_instanceof(il_factor_instanceof* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_instanceof;
	ret->u.instanceof_ = self;
	return ret;
}

il_factor_instanceof* il_factor_instanceof_new() {
	il_factor_instanceof* ret = (il_factor_instanceof*)MEM_MALLOC(sizeof(il_factor_instanceof));
	ret->fact = NULL;
	ret->cache = fqcn_cache_new();
	return ret;
}

void il_factor_instanceof_dump(il_factor_instanceof* self, int depth) {
	text_putindent(depth);
	text_printfln("instanceof");
	il_factor_dump(self->fact, depth + 1);
	fqcn_cache_dump(self->cache, depth + 1);
}

void il_factor_instanceof_load(il_factor_instanceof* self, enviroment* env, il_context* ilctx) {
	il_factor_load(self->fact, env, ilctx);
}

void il_factor_instanceof_generate(il_factor_instanceof* self, enviroment* env, il_context* ilctx) {
	generic_type* gtype = import_manager_resolvef(ilctx->class_loader_ref->import_manager, ILCTX_NAMESPACE(ilctx), self->cache, ilctx);
	type* type = gtype->core_type;
	assert(type != NULL);
	il_factor_generate(self->fact, env, ilctx);
	opcode_buf_add(env->buf, op_instanceof);
	opcode_buf_add(env->buf, type->absolute_index);
}

generic_type* il_factor_instanceof_eval(il_factor_instanceof* self, enviroment* env, il_context* ilctx) {
	return CL_BOOL->generic_self;
}

char* il_factor_instanceof_tostr(il_factor_instanceof* self, enviroment* env, il_context* ilctx) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, il_factor_tostr(self->fact, env, ilctx));
	string_buffer_appends(sb, " is ");
	string_buffer_appends(sb, fqcn_cache_tostr(self->cache));
	return string_buffer_release(sb);
}

void il_factor_instanceof_delete(il_factor_instanceof* self) {
	il_factor_delete(self->fact);
	fqcn_cache_delete(self->cache);
	MEM_FREE(self);
}