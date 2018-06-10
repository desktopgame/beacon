#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/xassert.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env);
static void resolve_default(il_factor_invoke_bound * self, enviroment * env);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env);
static void il_factor_invoke_bound_args_delete(vector_item item);

il_factor_invoke_bound* il_factor_invoke_bound_new(const char* name) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->name = text_strdup(name);
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
	text_printfln("%s", self->m->name);

	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_dump(e->factor, depth + 2);
	}
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env) {
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env);
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

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env) {
	ccpush_type_args(self->type_args);
	il_factor_invoke_bound_check(self, env);
	ccpop_type_args();
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env) {
	type* tp = cctop_type();
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env);
	if(il_error_panic()) {
		return NULL;
	}
	if(self->m->return_gtype->tag != generic_type_tag_none) {
		resolve_non_default(self, env);
		assert(self->resolved != NULL);
		return self->resolved;
	} else {
		resolve_default(self, env);
		assert(self->resolved != NULL);
		return self->resolved;
	}
	assert(self->resolved != NULL);
	return self->resolved;
}

char* il_factor_invoke_bound_tostr(il_factor_invoke_bound* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, self->name);
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->type_args, env);
	return string_buffer_release(sb);
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {
	vector_delete(self->args, il_factor_invoke_bound_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	//generic_type_delete(self->resolved);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = cctop_type();
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

static void resolve_default(il_factor_invoke_bound * self, enviroment * env) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	ccpush_type_args(self->type_args);
	self->resolved = generic_type_apply(rgtp);
	ccpop_type_args();
}

static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env) {
	if(self->index != -1) {
		return;
	}
	//対応するメソッドを検索
	type* ctype =cctop_type();
	int temp = -1;
	il_type_argument_resolve(self->type_args);
	ccpush_receiver(ctype->generic_self);
	ccpush_type_args(self->type_args);
	self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, &temp);
	self->index = temp;
	ccpop_receiver();
	ccpop_type_args();
	if(temp == -1) {
		il_error_report(ilerror_undefined_method, self->name);
	}
}
static void il_factor_invoke_bound_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}