#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../util/xassert.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"
#include "il_factor_variable_impl.h"
#include "../il_type_argument.h"
#include "../../env/type_interface.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/logger.h"
#include "../../env/type_impl.h"
#include <string.h>

//proto
static generic_type* il_factor_invoke_evalImpl(il_factor_invoke * self, enviroment * env, il_load_cache* cache);
static void il_factor_invoke_argument_delete(vector_item item);
static void il_factor_invoke_type_argument_delete(vector_item item);
static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env, il_load_cache* cache);

il_factor * il_factor_wrap_invoke(il_factor_invoke * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_invoke;
	ret->u.invoke_ = self;
	return ret;
}

il_factor_invoke * il_factor_invoke_new(const char * name) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	ret->type_argument_list = vector_new();
	ret->receiver = NULL;
	ret->m = NULL;
	ret->method_index = -1;
	ret->static_receiver = NULL;
	ret->return_type = NULL;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke * self, int depth) {
	text_putindent(depth);
	text_printf("invoke %s", self->name);
	il_type_argument_print(self->type_argument_list);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_invoke_generate(il_factor_invoke * self, enviroment* env, il_load_cache* cache) {
	il_factor_invoke_find(self, env, cache);
	//NOTE:Hoge.Foo() hoge.Foo() はil_named_invokeに拾われるので、
	//こちらでは関数の戻り値や式に対する呼び出しだけ考慮する。
	//全ての引数をプッシュ
	for(int i=0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env, cache);
	}
	//静的メソッドの場合
	if(modifier_is_static(self->m->modifier)) {
		opcode_buf_add(env->buf, (vector_item)op_invokestatic);
		opcode_buf_add(env->buf, (vector_item)self->m->gparent->core_type->absolute_index);
		opcode_buf_add(env->buf, (vector_item)self->method_index);
		return;
	}
	//このメソッドを呼び出しているオブジェクトをプッシュ
	il_factor_generate(self->receiver, env, cache);
	//メソッドのインデックスをプッシュ
	if (self->m->access == access_private) {
		opcode_buf_add(env->buf, (vector_item)op_invokespecial);
	} else {
		generic_type* receiverType = il_factor_eval(self->receiver, env, cache);
		type* core = receiverType->core_type;
		if (core->tag == type_class) {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokeinterface);
			opcode_buf_add(env->buf, receiverType->core_type->absolute_index);
			assert(receiverType->core_type->absolute_index != -1);
		}
	}
	opcode_buf_add(env->buf, (vector_item)self->method_index);
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
	if(self->receiver != NULL) {
		il_factor_load(self->receiver, env, cache, eh);
	}
	for(int i=0; i<self->argument_list->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->argument_list, i);
		il_factor_load(e->factor, env, cache, eh);
	}
}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	if(self->return_type != NULL) {
		return self->return_type;
	}
	//実行コンテキストを設定する
	vector_push(cache->receiver_vec, il_factor_eval(self->receiver, env, cache));
	vector_push(cache->type_args_vec, self->type_argument_list);
	//型を解析する
	generic_type* ret = il_factor_invoke_evalImpl(self, env, cache);
	self->return_type = ret;
	//コンテキストを戻す
	vector_pop(cache->receiver_vec);
	vector_pop(cache->type_args_vec);
	return self->return_type;
}

void il_factor_invoke_delete(il_factor_invoke * self) {
	vector_delete(self->argument_list, il_factor_invoke_argument_delete);
	vector_delete(self->type_argument_list, il_factor_invoke_type_argument_delete);
	MEM_FREE(self->name);
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}

//private
static generic_type* il_factor_invoke_evalImpl(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_invoke_find(self, env, cache);
	generic_type* gtp = self->m->return_gtype;
	bool a = XBREAKSTREQ(self->name, "iterate");
	if (gtp->virtual_type_index == -1) {
		XBREAK(a);
		return generic_type_apply(gtp, cache);
	}
	if (gtp->tag == generic_type_tag_class) {
		generic_type* class_gtp = il_factor_eval(self->receiver, env, cache);
		generic_type* ret = vector_at(class_gtp->type_args_list, gtp->virtual_type_index);
		XBREAK(a);
		return ret;
	}
	return gtp;
}

static void il_factor_invoke_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_type_argument_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env, il_load_cache* cache) {
	if(self->m != NULL) {
		return;
	}
	//実行するオブジェクトが変数の場合
	//静的メソッドの呼び出しかもしれないので検索
	if(self->receiver->type == ilfactor_variable) {
		namespace_* current = il_load_cache_namespace(cache);
		type* tp = namespace_get_type(current, self->receiver->u.variable_->name);
		if(tp != NULL) {
			int stemp = 0;
			method* meth = type_find_smethod(tp, self->name, self->argument_list, env, cache, &stemp);
			assert(meth != NULL);
			self->static_receiver = tp;
			self->m = meth;
			self->method_index = stemp;
			return;
		}
	}
	int temp = 0;
	generic_type* gtp = il_factor_eval(self->receiver, env, cache);
	self->m = generic_type_find_method(
		gtp,
		self->name,
		self->argument_list,
		env,
		cache,
		&temp
	);
	self->method_index = temp;
	assert(self->m != NULL);
}