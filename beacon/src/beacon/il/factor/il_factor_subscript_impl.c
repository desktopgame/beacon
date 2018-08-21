#include "il_factor_subscript_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../env/type_impl.h"
#include "../../env/operator_overload.h"

il_factor* il_factor_wrap_subscript(il_factor_subscript* self) {
	il_factor* ret = il_factor_new(ilfactor_subscript_T);
	ret->u.subscript = self;
	return ret;
}

il_factor_subscript* il_factor_subscript_malloc(const char* filename, int lineno) {
	il_factor_subscript* ret = mem_malloc(sizeof(il_factor_subscript), filename, lineno);
	ret->receiver = NULL;
	ret->pos = NULL;
	ret->operator_index = -1;
	ret->opov = NULL;
	return ret;
}

void il_factor_subscript_dump(il_factor_subscript* self, int depth) {
	io_printi(depth);
	io_printfln("[]");
	il_factor_dump(self->receiver, depth + 1);
	il_factor_dump(self->pos, depth + 1);
}

void il_factor_subscript_generate(il_factor_subscript* self, enviroment* env, call_context* cctx) {
	il_factor_generate(self->pos, env, cctx);
	il_factor_generate(self->receiver, env, cctx);
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, self->operator_index);
}

void il_factor_subscript_load(il_factor_subscript* self, enviroment* env, call_context* cctx) {
	if(self->operator_index != -1) {
		return;
	}
	il_factor_load(self->receiver, env, cctx);
	il_factor_load(self->pos, env, cctx);
	generic_type* receiver_gtype = il_factor_eval(self->receiver, env, cctx);
	generic_type* arg_gtype = il_factor_eval(self->pos, env, cctx);
	vector* args = vector_new();
	vector_push(args, arg_gtype);
	int temp = -1;
	self->opov = class_gfind_operator_overload(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), operator_sub_script_get_T, args, env, cctx, &temp);
	self->operator_index = temp;
	vector_delete(args, vector_deleter_null);
}

generic_type* il_factor_subscript_eval(il_factor_subscript* self, enviroment* env, call_context* cctx) {
	return generic_type_apply(self->opov->return_gtype, cctx);
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