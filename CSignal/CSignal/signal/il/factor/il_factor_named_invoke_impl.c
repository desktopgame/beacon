#include "il_factor_named_invoke_impl.h"
#include "../il_argument.h"
#include "../../env/method.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../util/logger.h"
#include "../../env/type_impl.h"
#include "il_factor_variable_impl.h"
#include <assert.h>

//proto
static void il_factor_named_invoke_delete_argument(vector_item item);
static void il_factor_named_invoke_find(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache);
static void il_factor_named_invoke_generate_IMPL(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache, type* tp);
static void il_factor_named_invoke_generate_STATIC_IMPL(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache, type* tp);
static void il_factor_named_invoke_generate_args(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache);

il_factor * il_factor_wrap_named_invoke(il_factor_named_invoke * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_named_invoke;
	ret->u.named_invoke_ = self;
	return ret;
}

il_factor_named_invoke * il_factor_named_invoke_new(const char* method_name) {
	il_factor_named_invoke* ret = (il_factor_named_invoke*)MEM_MALLOC(sizeof(il_factor_named_invoke));
	//ret->class_name = text_strdup(class_name);
	ret->method_name = text_strdup(method_name);
	ret->fqcn = fqcn_cache_new();
	ret->argument_list = vector_new();
	ret->type = ilnamed_invoke_static;
	ret->find = false;
	return ret;
}

void il_factor_named_invoke_dump(il_factor_named_invoke * self, int depth) {
	text_putindent(depth);
	text_printf("named invoke %s", self->method_name);
	text_putline();

	fqcn_cache_dump(self->fqcn, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_named_invoke_generate(il_factor_named_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_named_invoke_find(self, env, cache);
	//c.call() 変数への呼び出し
	if (self->type == ilnamed_invoke_variable) {
		il_factor_named_invoke_generate_args(self, env, cache);
		il_factor_generate(self->u.factor, env, cache);
		//継承出来ないなら
		if (self->m->access == access_private) {
			opcode_buf_add(env->buf, op_invokespecial);
		} else {
			//invokeinterface
			if (self->m->parent->tag == type_interface) {
				opcode_buf_add(env->buf, op_invokeinterface);
				opcode_buf_add(env->buf, self->m->parent->absolute_index);
				opcode_buf_add(env->buf, self->methodIndex);
			} else {
				opcode_buf_add(env->buf, op_invokevirtual);
				opcode_buf_add(env->buf, self->methodIndex);
			}
		}
	//C.call() クラスへの呼び出し
	} else {
		il_factor_named_invoke_generate_args(self, env, cache);
		opcode_buf_add(env->buf, op_invokestatic);
		opcode_buf_add(env->buf, self->m->parent->absolute_index);
		opcode_buf_add(env->buf, self->methodIndex);
	}
}

void il_factor_named_invoke_load(il_factor_named_invoke * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
}

type * il_factor_named_invoke_eval(il_factor_named_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_named_invoke_find(self, env, cache);
	return self->m->return_type;
}

void il_factor_named_invoke_delete(il_factor_named_invoke * self) {
	//MEM_FREE(self->fqcn);
	if (self->type == ilnamed_invoke_variable) {
		il_factor_delete(self->u.factor);
	}
	assert(self->fqcn->name != NULL);
	//MEM_FREE(self->fqcn->name);
	fqcn_cache_delete(self->fqcn);
	MEM_FREE(self->method_name);
	//vector_delete(self->fqcn->scope_vec, vector_deleter_free);
	vector_delete(self->argument_list, il_factor_named_invoke_delete_argument);
	MEM_FREE(self);
}


//private
static void il_factor_named_invoke_delete_argument(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_named_invoke_find(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache) {
	if (self->find) {
		return;
	}
	self->find = true;
	//X::Y.call() のような場合
	if (self->fqcn->scope_vec->length > 0) {
		namespace_* top = NULL;
		for (int i = 0; i < self->fqcn->scope_vec->length; i++) {
			char* e = (char*)vector_at(self->fqcn->scope_vec, i);
			if (top == NULL) {
				top = namespace_get_at_root(e);
			} else {
				top = namespace_get_namespace(top, e);
			}
		}
		type* tp = namespace_get_type(top, self->fqcn->name);
		il_factor_named_invoke_generate_STATIC_IMPL(self, env, cache, tp);
		//text_printf("%s %s", top->name, cls->name);
		self->u.type = tp;
		self->type = ilnamed_invoke_static;
	//Y.call() の場合
	} else {
		namespace_* top = (namespace_*)vector_top(cache->namespace_vec);
		//クラスが見つかった
		type* tp = NULL;
		if (top != NULL) {
			tp = namespace_get_type(top, self->fqcn->name);
		}
		//見つからないので signal::lang を補完
		if (tp == NULL) {
			tp = namespace_get_type(namespace_lang(), self->fqcn->name);
		}
		//見つかったなら静的呼び出し
		if (tp != NULL) {
			self->u.type = tp;
			self->type = ilnamed_invoke_static;
			il_factor_named_invoke_generate_STATIC_IMPL(self, env, cache, tp);
		//変数へのインスタンス呼び出し
		} else {
			self->u.factor = il_factor_wrap_variable(il_factor_variable_new(self->fqcn->name));
			self->type = ilnamed_invoke_variable;
			tp = il_factor_eval(self->u.factor, env, cache);
			il_factor_named_invoke_generate_IMPL(self, env, cache, tp);
		}
		//TEST(env->toplevel);
	}
}

static void il_factor_named_invoke_generate_IMPL(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache, type* tp) {
	//assert(tp->tag == type_class);
	//class_* cls = tp->u.class_;
	int temp = 0;
	self->m = type_find_method(tp, self->method_name, self->argument_list, env, cache, &temp);
	//self->m = class_find_method(cls, self->method_name, self->argument_list, env, &temp);
	assert(self->m != NULL);
	self->methodIndex = temp;
	//temp = 0;
	//TEST(env->toplevel);
}

static void il_factor_named_invoke_generate_STATIC_IMPL(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache, type* tp) {
	assert(tp->tag == type_class);
	class_* cls = tp->u.class_;
	int temp = 0;
	self->m = class_find_smethod(cls, self->method_name, self->argument_list, env, cache, &temp);
	self->methodIndex = temp;
	TEST(self->m == NULL);
	//temp = 0;
	//TEST(env->toplevel);
}

static void il_factor_named_invoke_generate_args(il_factor_named_invoke* self, enviroment* env, il_load_cache* cache) {
	//全ての引数をプッシュ
	for (int i = 0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env, cache);
	}
}