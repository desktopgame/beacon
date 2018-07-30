#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_args_delete(vector_item item);

il_factor_invoke_bound* il_factor_invoke_bound_new(string_view namev) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->namev = namev;
	ret->args = NULL;
	ret->type_args = NULL;
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_bound_dump(il_factor_invoke_bound* self, int depth) {
	text_putindent(depth);
	text_printfln("invoke bound");

	text_putindent(depth + 1);
	text_printfln("%s", string_pool_ref2str(self->m->namev));

	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_dump(e->factor, depth + 2);
	}
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cctx);
		if(il_error_panic()) {
			return;
		}
	}
	if(modifier_is_static(self->m->modifier)) {
		opcode_buf_add(env->buf, (vector_item)op_invokestatic);
		opcode_buf_add(env->buf,(vector_item) self->index);
	} else {
		opcode_buf_add(env->buf,(vector_item) op_this);
		if(self->m->access == access_private) {
			opcode_buf_add(env->buf, (vector_item)op_invokespecial);
			opcode_buf_add(env->buf, (vector_item)self->index);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
			opcode_buf_add(env->buf, (vector_item)self->index);
		}
	}
}

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_bound_check(self, env, cctx);
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	type* tp = NULL;
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env, cctx);
	if(il_error_panic()) {
		return NULL;
	}
	if(self->m->return_gtype->tag != generic_type_tag_none) {
		resolve_non_default(self, env, cctx);
		assert(self->resolved != NULL);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		assert(self->resolved != NULL);
		return self->resolved;
	}
	assert(self->resolved != NULL);
	return self->resolved;
}

char* il_factor_invoke_bound_tostr(il_factor_invoke_bound* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, string_pool_ref2str(self->namev));
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->type_args, env);
	return string_buffer_release(sb);
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {
	vector_delete(self->args, il_factor_invoke_bound_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	//generic_type_delete(self->resolved);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = NULL;
//	generic_type* receivergType = tp->generic_self;
	generic_type* rgtp  = self->m->return_gtype;
	if(rgtp->tag == generic_type_tag_class) {
		self->resolved = generic_type_new(NULL);
		self->resolved->tag = generic_type_tag_class;
		self->resolved->virtual_type_index = rgtp->virtual_type_index;
	} else if(rgtp->tag == generic_type_tag_method) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)vector_at(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_type_new(instanced_type->core_type);
		self->resolved->tag = generic_type_tag_class;
	}
}

static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	self->resolved = generic_type_apply(rgtp, cctx);
}

static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->index != -1) {
		return;
	}
	//対応するメソッドを検索
	type* ctype = call_context_type(cctx);
	int temp = -1;
	il_type_argument_resolve(self->type_args, cctx);
	for(int i=0; i<self->args->length; i++) {
		il_argument* ilarg = vector_at(self->args, i);
		il_factor_load(ilarg->factor, env, cctx);
	}
	call_frame* cfr = call_context_push(cctx, call_self_invoke_T);
	cfr->u.self_invoke.args = self->args;
	cfr->u.self_invoke.typeargs = self->type_args;
	self->m = class_ilfind_method(TYPE2CLASS(ctype), self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	call_context_pop(cctx);
	if(temp == -1) {
		il_error_report(ilerror_undefined_method, string_pool_ref2str(self->namev));
	}
}
static void il_factor_invoke_bound_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}