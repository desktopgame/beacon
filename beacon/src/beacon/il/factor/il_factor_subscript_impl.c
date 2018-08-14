#include "il_factor_subscript_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"

il_factor* il_factor_wrap_subscript(il_factor_subscript* self) {
	il_factor* ret = il_factor_new(ilfactor_subscript);
	ret->u.subscript = self;
	return ret;
}

il_factor_subscript* il_factor_subscript_malloc(const char* filename, int lineno) {
	il_factor_subscript* ret = mem_malloc(sizeof(il_factor_subscript), filename, lineno);
	ret->receiver = NULL;
	ret->pos = NULL;
	return ret;
}

void il_factor_subscript_dump(il_factor_subscript* self, int depth) {
	io_printi(depth);
	io_printfln("[]");
	il_factor_dump(self->receiver, depth + 1);
	il_factor_dump(self->pos, depth + 1);
}

void il_factor_subscript_generate(il_factor_subscript* self, enviroment* env, call_context* cctx) {
}

void il_factor_subscript_load(il_factor_subscript* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->receiver, env, cctx);
	il_factor_load(self->pos, env, cctx);
}

generic_type* il_factor_subscript_eval(il_factor_subscript* self, enviroment* env, call_context* cctx) {
	return NULL;
}

char* il_factor_subscript_tostr(il_factor_subscript* self, enviroment* env) {
	string_buffer* buf = string_buffer_new();
	char* src = il_factor_tostr(self->receiver, env);
	char* pos = il_factor_tostr(self->pos, env);
	string_buffer_appends(buf, src);
	string_buffer_append(buf, '[');
	string_buffer_appends(buf, pos);
	string_buffer_append(buf, ']');
	MEM_FREE(src);
	MEM_FREE(pos);
	return string_buffer_release(buf);
}

void il_factor_subscript_delete(il_factor_subscript* self) {
	il_factor_delete(self->receiver);
	il_factor_delete(self->pos);
	MEM_FREE(self);
}