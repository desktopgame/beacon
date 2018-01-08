#include "il_factor_call_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../il_argument.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"

//proto
static void il_factor_call_argument_list_delete(vector_item item);
static void il_factor_find_method(il_factor_call* self, enviroment* env);

il_factor * il_factor_wrap_call(il_factor_call * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_call;
	ret->u.call_ = self;
	return ret;
}

il_factor_call * il_factor_call_new(const char * name) {
	il_factor_call* ret = (il_factor_call*)MEM_MALLOC(sizeof(il_factor_call));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	ret->m = NULL;
	ret->methodIndex = -1;
	return ret;
}

void il_factor_call_dump(il_factor_call * self, int depth) {
	text_putindent(depth);
	printf("call %s", self->name);
	text_putline();
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_call_generate(il_factor_call * self, enviroment* env) {
	il_factor_find_method(self, env);
	//全ての引数をスタックへ積む
	for(int i=0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env);
	}
	if (modifier_is_static(self->m->modifier)) {
		opcode_buf_add(env->buf, (vector_item)op_invokestatic);
		opcode_buf_add(env->buf, self->m->parent->absoluteIndex);
		opcode_buf_add(env->buf, (vector_item)self->methodIndex);
		return;
	}
	//呼び出すメソッドの位置をスタックに積む
	//ここで直接メソッドのポインタを積まないのはあとでシリアライズするときのため。
	if (self->m->access == access_private) {
		opcode_buf_add(env->buf, (vector_item)op_invokespecial);
		opcode_buf_add(env->buf, (vector_item)self->methodIndex);
	} else {
		opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
		opcode_buf_add(env->buf, (vector_item)self->methodIndex);
	}
}

void il_factor_call_load(il_factor_call * self, enviroment * env, il_ehandler * eh) {
}

type * il_factor_call_eval(il_factor_call * self, enviroment * env) {
	il_factor_find_method(self, env);
	return self->m->return_type;
}

void il_factor_call_delete(il_factor_call * self) {
	vector_delete(self->argument_list, il_factor_call_argument_list_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_factor_call_argument_list_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_find_method(il_factor_call* self, enviroment* env) {
	if(self->m != NULL) {
		return;
	}
	int temp = 0;
	type* tp = (type*)vector_top(env->class_vec);
	class_* cls = tp->u.class_;
	self->m = class_find_method(cls, self->name, self->argument_list, env, &temp);
	self->methodIndex = temp;
	if (self->m == NULL) {
		self->m = class_find_smethod(cls, self->name, self->argument_list, env, &temp);
		self->methodIndex = temp;
	}
}