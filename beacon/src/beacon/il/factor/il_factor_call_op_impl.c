#include "il_factor_call_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../il_factor_impl.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include <string.h>
#include <assert.h>

//proto
static void il_factor_call_op_check(il_factor_call_op* self, enviroment* env, il_load_cache* cache);
static void il_factor_call_op_argument_delete(vector_item item);
static void il_factor_call_op_type_argument_delete(vector_item item);

il_factor* il_factor_wrap_call_op(il_factor_call_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_call_op;
	ret->u.call_ = self;
	self->parent = ret;
	return ret;
}

il_factor_call_op* il_factor_call_op_new() {
	il_factor_call_op* ret = (il_factor_call_op*)MEM_MALLOC(sizeof(il_factor_call_op));
	ret->receiver = NULL;
	ret->argument_list = vector_new();
	ret->type = ilcall_type_undefined;
	return ret;
}

void il_factor_call_op_dump(il_factor_call_op* self, int depth) {
	text_putindent(depth);
	text_printf("call");
	il_factor_dump(self->receiver, depth + 1);
	for(int i=0; i<self->argument_list->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->argument_list, i);
		il_argument_dump(e, depth + 1);
	}
}

void il_factor_call_op_load(il_factor_call_op* self, enviroment* env, il_load_cache* cache, il_ehandler* eh) {
	il_factor_call_op_check(self, env, cache);
	if(self->type == ilcall_type_invoke) {
		il_factor_invoke_load(self->u.invoke_, env, cache, eh);
	} else if(self->type == ilcall_type_invoke_static) {
		il_factor_invoke_static_load(self->u.invoke_static_, env, cache, eh);
	} else if(self->type == ilcall_type_invoke_bound) {
		il_factor_invoke_bound_load(self->u.invoke_bound_, env, cache, eh);
	}
}

generic_type* il_factor_call_op_eval(il_factor_call_op* self, enviroment* env, il_load_cache* cache) {
	il_factor_call_op_check(self, env, cache);
	if(self->type == ilcall_type_invoke) {
		return il_factor_invoke_eval(self->u.invoke_, env, cache);
	} else if(self->type == ilcall_type_invoke_static) {
		return il_factor_invoke_static_eval(self->u.invoke_static_, env, cache);
	} else if(self->type == ilcall_type_invoke_bound) {
		return il_factor_invoke_bound_eval(self->u.invoke_bound_, env, cache);
	}
	return NULL;
}

void il_factor_call_op_generate(il_factor_call_op* self, enviroment* env, il_load_cache* cache) {
	il_factor_call_op_load(self, env, cache, NULL);
	if(self->type == ilcall_type_invoke) {
		return il_factor_invoke_generate(self->u.invoke_, env, cache);
	} else if(self->type == ilcall_type_invoke_static) {
		return il_factor_invoke_static_generate(self->u.invoke_static_, env, cache);
	} else if(self->type == ilcall_type_invoke_bound) {
		return il_factor_invoke_bound_generate(self->u.invoke_bound_, env, cache);
	}
}

void il_factor_call_op_delete(il_factor_call_op* self) {
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}

il_factor_call_op* il_factor_cast_call_op(il_factor* fact) {
	assert(fact->type == ilfactor_call_op);
	return fact->u.call_;
}

//private
static void il_factor_call_op_check(il_factor_call_op* self, enviroment* env, il_load_cache* cache) {
	if(self->type != ilcall_type_undefined) {
		return;
	}
	il_factor* receiver = self->receiver;
	//hoge() foo() Namespace::Class() の場合
	if(receiver->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(receiver);
		il_factor_invoke_bound* bnd = il_factor_invoke_bound_new(ilvar->fqcn->name);
		assert(ilvar->fqcn->scope_vec->length == 0);
		//入れ替え
		bnd->args = self->argument_list;
		bnd->type_args = ilvar->type_args;
		self->argument_list = NULL;
		ilvar->type_args = NULL;
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->type == ilfactor_member_op) {
		il_factor_member_op* ilmem = IL_FACT2MEM(receiver);
		self->type = ilcall_type_invoke;
		//hoge.foo
		if(ilmem->fact->type == ilfactor_variable) {
			il_factor_variable* ilvar = IL_FACT2VAR(ilmem->fact);
			//Namespace::Class.foo()
			if(ilvar->fqcn->scope_vec->length > 0) {
				il_factor_invoke_static* st = il_factor_invoke_static_new();
				self->type = ilcall_type_invoke_static;
				self->u.invoke_static_ = st;
				//入れ替える
				st->type_args = ilvar->type_args;
				st->args = self->argument_list;
				st->fqcn = ilvar->fqcn;
				self->argument_list = NULL;
				ilvar->type_args = NULL;
				ilvar->fqcn = NULL;
			//hoge.foo()
			} else {
				il_factor_invoke* iv = il_factor_invoke_new();
				//入れ替える
				iv->args = self->argument_list;
				iv->receiver = ilmem->fact;
				iv->type_args = ilvar->type_args;
				ilmem->fact = NULL;
				ilvar->type_args = NULL;
			}
		}
	}
}

static void il_factor_call_op_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_call_op_type_argument_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}