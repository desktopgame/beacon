#include "il_factor_named_invoke_impl.h"
#include "../il_argument.h"
#include "../../env/method.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include <assert.h>

//proto
static void il_factor_named_invoke_delete_argument(vector_item item);
static void il_factor_named_invoke_find(il_factor_named_invoke* self, enviroment* env);
static void il_factor_named_invoke_generate_args(il_factor_named_invoke* self, enviroment* env);

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
	return ret;
}

void il_factor_named_invoke_dump(il_factor_named_invoke * self, int depth) {
	text_putindent(depth);
	printf("named invoke %s", self->method_name);
	text_putline();

	fqcn_cache_dump(self->fqcn, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_named_invoke_generate(il_factor_named_invoke * self, enviroment * env) {
	il_factor_named_invoke_find(self, env);
	//c.call() 変数への呼び出し
	if (self->type == ilnamed_invoke_variable) {
		il_factor_generate(self->u.factor, env);
		il_factor_named_invoke_generate_args(self, env);
		opcode_buf_add(env->buf, (vector_item)op_method);
		opcode_buf_add(env->buf, self->methodIndex);
		opcode_buf_add(env->buf, op_invokevirtual);
	//C.call() クラスへの呼び出し
	} else {
		il_factor_named_invoke_generate_args(self, env);
		opcode_buf_add(env->buf, (vector_item)op_static_method);
		opcode_buf_add(env->buf, self->m->parent->absoluteIndex);
		opcode_buf_add(env->buf, self->methodIndex);
		opcode_buf_add(env->buf, op_invokestatic);
	}
}

class_ * il_factor_named_invoke_eval(il_factor_named_invoke * self, enviroment * env) {
	il_factor_named_invoke_find(self, env);
	return self->m->return_type;
}

void il_factor_named_invoke_delete(il_factor_named_invoke * self) {
	//MEM_FREE(self->fqcn);
	assert(self->fqcn->name != NULL);
	MEM_FREE(self->fqcn->name);
	MEM_FREE(self->method_name);
	vector_delete(self->fqcn->scope_vec, vector_deleter_free);
	vector_delete(self->argument_list, il_factor_named_invoke_delete_argument);
	MEM_FREE(self);
}


//private
static void il_factor_named_invoke_delete_argument(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_named_invoke_find(il_factor_named_invoke* self, enviroment* env) {
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
		class_* cls = namespace_get_class(top, self->fqcn->name);
		int temp = 0;
		self->m = class_find_methodvf(cls, self->method_name, self->argument_list, env, &temp);
		self->methodIndex = temp;
		//printf("%s %s", top->name, cls->name);
		self->u.classz = cls;
		self->type = ilnamed_invoke_static;
	//Y.call() の場合
	} else {
		namespace_* top = NULL;
		//クラスが見つかった
		class_* cls = namespace_get_class(top, self->fqcn->name);
		if (cls != NULL) {
			self->u.classz = cls;
			self->type = ilnamed_invoke_static;
		} else {
			self->u.factor = il_factor_variable_new(self->fqcn->name);
			self->type = ilnamed_invoke_variable;
		}
	}
}

static void il_factor_named_invoke_generate_args(il_factor_named_invoke* self, enviroment* env) {
	//全ての引数をプッシュ
	for (int i = 0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env);
	}
}