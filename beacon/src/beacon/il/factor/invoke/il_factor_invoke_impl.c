#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/method.h"
#include "../../../env/class_loader.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../il_factor_impl.h"
#include <string.h>
#include <stdio.h>

//proto
static void resolve_non_default(il_factor_invoke * self, enviroment * env, call_context* cctx);
static void resolve_default(il_factor_invoke * self, enviroment * env, call_context* cctx);
static void il_factor_invoke_args_delete(vector_item item);
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, call_context* cctx);

il_factor_invoke* il_factor_invoke_new(string_view namev) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->m = NULL;
	ret->namev = namev;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke* self, int depth) {
	io_printi(depth);
	io_printfln("invoke");

	il_factor_dump(self->receiver, depth + 1);

	io_printi(depth + 1);
	io_printfln("%s", string_pool_ref2str(self->m->namev));

	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_dump(e->factor, depth + 2);
	}
}

void il_factor_invoke_generate(il_factor_invoke* self, enviroment* env, call_context* cctx) {
	for(int i=0; i<self->type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(self->type_args, i);
		assert(e->gtype != NULL);
		opcode_buf_add(env->buf, op_generic_add);
		generic_type_generate(e->gtype, env);
	}
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cctx);
	}
	il_factor_generate(self->receiver, env, cctx);
	if(self->m->parent->tag == type_interface) {
		opcode_buf_add(env->buf, (vector_item)op_invokeinterface);
		opcode_buf_add(env->buf, (vector_item)self->m->parent->absolute_index);
		opcode_buf_add(env->buf, (vector_item)self->index);
	} else {
		assert(!modifier_is_static(self->m->modifier));
		if(self->m->access == access_private) {
			opcode_buf_add(env->buf, (vector_item)op_invokespecial);
			opcode_buf_add(env->buf, (vector_item)self->index);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
			opcode_buf_add(env->buf, (vector_item)self->index);
		}
	}
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	call_frame* cfr = call_context_push(cctx, frame_instance_invoke_T);
	cfr->u.instance_invoke.args = self->args;
	cfr->u.instance_invoke.typeargs = self->type_args;
	cfr->u.instance_invoke.receiver = il_factor_eval(self->receiver, env, cctx);
	il_factor_load(self->receiver, env, cctx);
	il_factor_invoke_check(self, env, cctx);
	call_context_pop(cctx);
}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	il_factor_invoke_check(self, env, cctx);
	if(bc_error_last()) {
		return NULL;
	}
	generic_type* rgtp = self->m->return_gtype;
	generic_type* ret = NULL;
	//型変数をそのまま返す場合
	if(rgtp->tag != generic_type_tag_none) {
		resolve_non_default(self, env, cctx);
		ret = self->resolved;
	//型変数ではない型を返す
	} else {
		resolve_default(self, env, cctx);
		ret = self->resolved;
	}
	return ret;
}

char* il_factor_invoke_tostr(il_factor_invoke* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* invstr = il_factor_tostr(self->receiver, env);
	string_buffer_appends(sb, invstr);
	string_buffer_append(sb, '.');
	string_buffer_appends(sb, string_pool_ref2str(self->namev));
	il_factor_type_args_tostr(sb, self->type_args, env);
	il_factor_args_tostr(sb, self->type_args, env);
	MEM_FREE(invstr);
	return string_buffer_release(sb);
}

void il_factor_invoke_delete(il_factor_invoke* self) {
	vector_delete(self->args, il_factor_invoke_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	il_factor_delete(self->receiver);
	//generic_type_delete(self->resolved);
	MEM_FREE(self);
}
//private
static void resolve_non_default(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = il_factor_eval(self->receiver, env, cctx);
	generic_type* rgtp = self->m->return_gtype;
	if(rgtp->tag == generic_type_tag_class) {
		//レシーバの実体化された型の中で、
		//メソッドの戻り値 'T' が表す位置に対応する実際の型を取り出す。
		generic_type* instanced_type = (generic_type*)vector_at(receivergType->type_args_list, rgtp->virtual_type_index);
		self->resolved = generic_type_clone(instanced_type);
		self->resolved->tag = generic_type_tag_class;
	} else if(rgtp->tag == generic_type_tag_method) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)vector_at(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_type_clone(instanced_type);
		self->resolved->tag = generic_type_tag_class;
	}
}

static void resolve_default(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = il_factor_eval(self->receiver, env, cctx);
	generic_type* rgtp = self->m->return_gtype;
//	virtual_type returnvType = self->m->return_vtype;
	//内側に型変数が含まれているかもしれないので、
	//それをここで展開する。
	call_frame* cfr = call_context_push(cctx, frame_instance_invoke_T);
	cfr->u.instance_invoke.receiver = receivergType;
	cfr->u.instance_invoke.args = self->args;
	cfr->u.instance_invoke.typeargs = self->type_args;
	self->resolved = generic_type_apply(rgtp, cctx);
	call_context_pop(cctx);
}

static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, call_context* cctx) {
	//レシーバの読み込み
	il_factor_load(self->receiver, env, cctx);
	if(bc_error_last()) {
		return;
	}
	if(self->receiver->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(self->receiver);
		assert(ilvar->type != ilvariable_type_static);
	}
	//レシーバの型を評価
	generic_type* gtype = il_factor_eval(self->receiver, env, cctx);
	if(bc_error_last()) {
		return;
	}
	//対応するメソッドを検索
	il_type_argument_resolve(self->type_args, cctx);

	type* ctype = gtype->core_type;
	#if defined(DEBUG)
	const char* cname = string_pool_ref2str(type_name(ctype));
	#endif
	//ジェネリックな変数に対しても
	//Objectクラスのメソッドは呼び出せる
	if(ctype == NULL) {
		ctype = TYPE_OBJECT;
	}
	assert(ctype != NULL);
	int temp = -1;
	self->m = type_ilfind_method(ctype, self->namev, self->args, env, cctx, &temp);
	//self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, cache, &temp);
	self->index = temp;
	if(temp == -1) {
		bc_error_throw(bcerror_undefined_method, string_pool_ref2str(self->namev));
		return;
	}
}

static void il_factor_invoke_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}