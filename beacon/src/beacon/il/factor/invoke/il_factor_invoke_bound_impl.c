#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/symbol_entry.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void il_factor_invoke_bound_delete_typeargs(vector_item item);
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_bound_args_delete(vector_item item);
static void il_factor_invoke_bound_generate_method(il_factor_invoke_bound* self, enviroment* env, call_context* cctx);
static void il_factor_invoke_bound_generate_subscript(il_factor_invoke_bound* self, enviroment* env, call_context* cctx);
static generic_type* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, call_context* cctx);
static generic_type* il_factor_invoke_bound_evalImpl(il_factor_invoke_bound * self, enviroment * env, call_context* cctx);

il_factor_invoke_bound* il_factor_invoke_bound_new(string_view namev) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->namev = namev;
	ret->args = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	ret->tag = bound_invoke_undefined_T;
	return ret;
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	il_factor_invoke_bound_generate_method(self, env, cctx);
	il_factor_invoke_bound_generate_subscript(self, env, cctx);
}

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_bound_check(self, env, cctx);
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	generic_type* ret = il_factor_invoke_bound_evalImpl(self, env, cctx);
	assert(ret != NULL);
	return ret;
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
	vector_delete(self->type_args, il_factor_invoke_bound_delete_typeargs);
	//generic_type_delete(self->resolved);
	MEM_FREE(self);
}

operator_overload* il_factor_invoke_bound_find_set(il_factor_invoke_bound* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex) {
	assert(self->tag == bound_invoke_subscript_T);
	vector* args = vector_new();
	vector_push(args, ((il_argument*)vector_at(self->args, 0))->factor);
	vector_push(args, value);
	operator_overload* opov = class_ilfind_operator_overload(TYPE2CLASS(self->u.subscript.opov->parent), operator_sub_script_set_T, args, env, cctx, outIndex);
	vector_delete(args, vector_deleter_null);
	return opov;
}

//private
//FIXME:il_factor_invokeからのコピペ
static void il_factor_invoke_bound_delete_typeargs(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = NULL;
	generic_type* rgtp  = il_factor_invoke_bound_return_gtype(self, cctx);
	if(rgtp->tag == generic_type_tag_class_T) {
		self->resolved = generic_type_new(NULL);
		self->resolved->tag = generic_type_tag_class_T;
		self->resolved->virtual_type_index = rgtp->virtual_type_index;
	} else if(rgtp->tag == generic_type_tag_method_T) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)vector_at(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_type_new(instanced_type->core_type);
		self->resolved->tag = generic_type_tag_class_T;
	}
}

static void resolve_default(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* rgtp = il_factor_invoke_bound_return_gtype(self, cctx);
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
	BC_ERROR();
	#if defined(DEBUG)
	const char* nstr = string_pool_ref2str(self->namev);
	const char* str = string_pool_ref2str(type_name(ctype));
	#endif
	call_frame* cfr = call_context_push(cctx, frame_self_invoke_T);
	cfr->u.self_invoke.args = self->args;
	cfr->u.self_invoke.typeargs = self->type_args;
	self->tag = bound_invoke_method_T;
	self->u.m = class_ilfind_method(TYPE2CLASS(ctype), self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	BC_ERROR();
	if(self->index != -1) {
		call_context_pop(cctx);
		return;
	}
	//添字アクセスとして解決する
	generic_type* receiver_gtype = NULL;
	symbol_entry* local = symbol_table_entry(env->sym_table, NULL, self->namev);
	if(receiver_gtype == NULL && local != NULL) {
		receiver_gtype = local->gtype;
		self->u.subscript.tag = subscript_local_T;
		self->u.subscript.u.local = local;
		self->u.subscript.index = local->index;
	}
	//フィールドとして解決する
	field* fi = class_find_field(call_context_class(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && fi != NULL) {
		receiver_gtype = fi->gtype;
		self->u.subscript.tag = subscript_field_T;
		self->u.subscript.u.fi = fi;
		self->u.subscript.index = temp;
	}
	//プロパティとして解決する
	property* prop = class_find_property(call_context_class(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && prop != NULL) {
		receiver_gtype = prop->gtype;
		self->u.subscript.tag = subscript_property_T;
		self->u.subscript.u.prop = prop;
		self->u.subscript.index = temp;
	}
	if(receiver_gtype != NULL) {
		self->tag = bound_invoke_subscript_T;
		self->u.subscript.opov = class_argfind_operator_overload(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), operator_sub_script_get_T, self->args, env, cctx, &temp);
		self->index = temp;
		if(temp == -1) {
			bc_error_throw(bcerror_invoke_bound_undefined_method_T,
				string_pool_ref2str(self->namev)
			);
		}
	}
	if(self->index == -1) {
		bc_error_throw(bcerror_invoke_bound_undefined_method_T,
			string_pool_ref2str(type_name(ctype)),
			string_pool_ref2str(self->namev)
		);
	}
	call_context_pop(cctx);
}

static void il_factor_invoke_bound_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_bound_generate_method(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	assert(self->tag != bound_invoke_undefined_T);
	if(self->tag != bound_invoke_method_T) {
		return;
	}
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cctx);
		if(bc_error_last()) {
			return;
		}
	}
	if(modifier_is_static(self->u.m->modifier)) {
		opcode_buf_add(env->buf, (vector_item)op_invokestatic);
		opcode_buf_add(env->buf, (vector_item)self->u.m->parent->absolute_index);
		opcode_buf_add(env->buf,(vector_item) self->index);
	} else {
		opcode_buf_add(env->buf,(vector_item) op_this);
		if(self->u.m->access == access_private_T) {
			opcode_buf_add(env->buf, (vector_item)op_invokespecial);
			opcode_buf_add(env->buf, (vector_item)self->index);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
			opcode_buf_add(env->buf, (vector_item)self->index);
		}
	}
}

static void il_factor_invoke_bound_generate_subscript(il_factor_invoke_bound* self, enviroment* env, call_context* cctx) {
	assert(self->tag != bound_invoke_undefined_T);
	if(self->tag != bound_invoke_subscript_T) {
		return;
	}
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cctx);
		if(bc_error_last()) {
			return;
		}
	}
	subscript_descriptor subs = self->u.subscript;
	if(subs.tag == subscript_local_T) {
		opcode_buf_add(env->buf, op_load);
		opcode_buf_add(env->buf, subs.index);
	} else if(subs.tag == subscript_field_T) {
		opcode_buf_add(env->buf, op_this);
		generate_get_field(env->buf, subs.u.fi, subs.index);
	} else if(subs.tag == subscript_property_T) {
		opcode_buf_add(env->buf, op_this);
		generate_get_property(env->buf, subs.u.prop, subs.index);
	} else {
		assert(false);
	}
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, self->index);
}

static generic_type* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, call_context* cctx) {
	assert(self->tag != bound_invoke_undefined_T);
	return generic_type_apply(self->tag == bound_invoke_method_T ?
			self->u.m->return_gtype :
			self->u.subscript.opov->return_gtype, cctx);
}

static generic_type* il_factor_invoke_bound_evalImpl(il_factor_invoke_bound * self, enviroment * env, call_context* cctx) {
	type* tp = NULL;
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env, cctx);
	if(bc_error_last()) {
		return NULL;
	}
	call_frame* cfr = NULL;
	if(self->tag == bound_invoke_method_T) {
		cfr = call_context_push(cctx, frame_self_invoke_T);
		cfr->u.self_invoke.args = self->args;
		cfr->u.self_invoke.typeargs = self->type_args;
	} else {
		cfr = call_context_push(cctx, frame_instance_invoke_T);
		cfr->u.instance_invoke.receiver = generic_type_apply(subscript_descriptor_receiver(&self->u.subscript), cctx);
		cfr->u.instance_invoke.args = self->args;
		cfr->u.instance_invoke.typeargs = self->type_args;
	}

	if(il_factor_invoke_bound_return_gtype(self, cctx)->tag != generic_type_tag_none_T) {
		resolve_non_default(self, env, cctx);
		assert(self->resolved != NULL);
		call_context_pop(cctx);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		assert(self->resolved != NULL);
		call_context_pop(cctx);
		return self->resolved;
	}
	call_context_pop(cctx);
	assert(self->resolved != NULL);
	return self->resolved;
}