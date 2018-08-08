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
	il_factor* ret = il_factor_new(ilfactor_instanceof);
	ret->u.instanceof_ = self;
	return ret;
}

il_factor_instanceof* il_factor_instanceof_new() {
	il_factor_instanceof* ret = (il_factor_instanceof*)MEM_MALLOC(sizeof(il_factor_instanceof));
	ret->fact = NULL;
	ret->gcache = generic_cache_new();
	return ret;
}

void il_factor_instanceof_dump(il_factor_instanceof* self, int depth) {
	io_printi(depth);
	io_printfln("instanceof");
	il_factor_dump(self->fact, depth + 1);
	generic_cache_dump(self->gcache, depth + 1);
}

void il_factor_instanceof_load(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->fact, env, cctx);
}

void il_factor_instanceof_generate(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	generic_type* gtype = import_manager_resolve(NULL, NULL, self->gcache, cctx);
	type* type = gtype->core_type;
	assert(type != NULL);
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_generic_add);
	generic_type_generate(gtype, env);
	opcode_buf_add(env->buf, op_instanceof);
}

generic_type* il_factor_instanceof_eval(il_factor_instanceof* self, enviroment* env, call_context* cctx) {
	return TYPE_BOOL->generic_self;
}

char* il_factor_instanceof_tostr(il_factor_instanceof* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* a = il_factor_tostr(self->fact, env);
	char* b = generic_cache_tostr(self->gcache);
	string_buffer_appends(sb, a);
	string_buffer_appends(sb, " is ");
	string_buffer_appends(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return string_buffer_release(sb);
}

void il_factor_instanceof_delete(il_factor_instanceof* self) {
	il_factor_delete(self->fact);
	generic_cache_delete(self->gcache);
	MEM_FREE(self);
}