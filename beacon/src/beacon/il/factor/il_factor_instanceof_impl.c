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
	il_factor* ret = il_factor_new(ILFACTOR_INSTANCEOF_T);
	ret->u.instanceof_ = self;
	return ret;
}

il_factor_instanceof* il_factor_instanceof_new() {
	il_factor_instanceof* ret = (il_factor_instanceof*)MEM_MALLOC(sizeof(il_factor_instanceof));
	ret->fact = NULL;
	ret->gcache = generic_cache_new();
	return ret;
}

void il_factor_instanceof_load(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->fact, env, cctx);
}

void il_factor_instanceof_generate(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	generic_type* gtype = import_manager_resolve(NULL, self->gcache, cctx);
	type* type = gtype->core_type;
	il_factor_generate(self->fact, env, cctx);
	AddOpcodeBuf(env->buf, OP_GENERIC_ADD);
	generic_type_generate(gtype, env);
	AddOpcodeBuf(env->buf, OP_INSTANCEOF);
}

generic_type* il_factor_instanceof_eval(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	return TYPE_BOOL->generic_self;
}

char* il_factor_instanceof_tostr(il_factor_instanceof* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* a = il_factor_tostr(self->fact, env);
	char* b = generic_cache_tostr(self->gcache);
	AppendsBuffer(sb, a);
	AppendsBuffer(sb, " is ");
	AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return ReleaseBuffer(sb);
}

void il_factor_instanceof_delete(il_factor_instanceof* self) {
	il_factor_delete(self->fact);
	generic_cache_delete(self->gcache);
	MEM_FREE(self);
}