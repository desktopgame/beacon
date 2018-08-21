#include "il_factor_call_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../il_factor_impl.h"
#include "../../env/namespace.h"
#include "../../env/type/class_impl.h"
#include "../../vm/enviroment.h"
#include <string.h>
#include <assert.h>

//proto
static void il_factor_call_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx);
static void il_factor_member_op_check_namebase(il_factor_call_op* self, il_factor_member_op* ilmem, enviroment* env, call_context* cctx);
static void il_factor_member_op_check_instance(il_factor_call_op* self, il_factor_member_op* ilmem, enviroment* env, call_context* cctx);
static void il_factor_member_op_check_static(il_factor_call_op* self, il_factor_member_op* ilmem, il_factor_variable* ilvar, enviroment* env, call_context* cctx);
static void il_factor_invoke_bound_check(il_factor_call_op* self, enviroment* env);
static void il_factor_member_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx);
static void il_factor_subscript_check(il_factor_call_op* self, enviroment* env, call_context* cctx);

static void il_factor_call_op_argument_delete(vector_item item);
static void il_factor_call_op_type_argument_delete(vector_item item);

il_factor* il_factor_wrap_call_op(il_factor_call_op* self) {
	il_factor* ret = il_factor_new(ilfactor_call_op_T);
	ret->u.call_ = self;
	self->parent = ret;
	return ret;
}

il_factor_call_op* il_factor_call_op_new() {
	il_factor_call_op* ret = (il_factor_call_op*)MEM_MALLOC(sizeof(il_factor_call_op));
	ret->receiver = NULL;
	ret->argument_list = vector_new();
	ret->type = ilcall_type_undefined_T;
	return ret;
}

void il_factor_call_op_dump(il_factor_call_op* self, int depth) {
	if(self->type == ilcall_type_invoke_T) {
		il_factor_invoke_dump(self->u.invoke_, depth);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		il_factor_invoke_bound_dump(self->u.invoke_bound_, depth);
	} else if(self->type == ilcall_type_invoke_static_T) {
		il_factor_invoke_static_dump(self->u.invoke_static_, depth);
	} else {
		io_printi(depth);
		printf("call");
		il_factor_dump(self->receiver, depth + 1);
		for(int i=0; i<self->argument_list->length; i++) {
			il_argument* e = (il_argument*)vector_at(self->argument_list, i);
			il_argument_dump(e, depth + 1);
		}
	}
}

void il_factor_call_op_load(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	//argumentlistはサブクラスに渡しちゃってる
	//il_factor_load(self->receiver, env, ilctx, eh);
	il_factor_call_op_check(self, env, cctx);
	if(self->type == ilcall_type_invoke_T) {
		il_factor_invoke_load(self->u.invoke_, env, cctx);
	} else if(self->type == ilcall_type_invoke_static_T) {
		il_factor_invoke_static_load(self->u.invoke_static_, env, cctx);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		il_factor_invoke_bound_load(self->u.invoke_bound_, env, cctx);
	}
}

generic_type* il_factor_call_op_eval(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor_call_op_check(self, env, cctx);
	generic_type* ret = NULL;
	if(self->type == ilcall_type_invoke_T) {
		ret = il_factor_invoke_eval(self->u.invoke_, env, cctx);
	} else if(self->type == ilcall_type_invoke_static_T) {
		ret =  il_factor_invoke_static_eval(self->u.invoke_static_, env, cctx);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		ret = il_factor_invoke_bound_eval(self->u.invoke_bound_, env, cctx);
	}
	if(bc_error_last()) {
		return ret;
	}
	return ret;
}

char* il_factor_call_op_to_str(il_factor_call_op* self, enviroment* env) {
//	il_factor_call_op_load(self, env);
	if(self->type == ilcall_type_invoke_T) {
		return il_factor_invoke_tostr(self->u.invoke_, env);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		return il_factor_invoke_bound_tostr(self->u.invoke_bound_, env);
	} else if(self->type == ilcall_type_invoke_static_T) {
		return il_factor_invoke_static_tostr(self->u.invoke_static_, env);
	}
	return NULL;
}

void il_factor_call_op_generate(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor_call_op_load(self, env, cctx);
	if(self->type == ilcall_type_invoke_T) {
		return il_factor_invoke_generate(self->u.invoke_, env, cctx);
	} else if(self->type == ilcall_type_invoke_static_T) {
		return il_factor_invoke_static_generate(self->u.invoke_static_, env, cctx);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		return il_factor_invoke_bound_generate(self->u.invoke_bound_, env, cctx);
	}
}

void il_factor_call_op_delete(il_factor_call_op* self) {
	il_factor_delete(self->receiver);
	if(self->type == ilcall_type_invoke_T) {
		il_factor_invoke_delete(self->u.invoke_);
	} else if(self->type == ilcall_type_invoke_static_T) {
		il_factor_invoke_static_delete(self->u.invoke_static_);
	} else if(self->type == ilcall_type_invoke_bound_T) {
		il_factor_invoke_bound_delete(self->u.invoke_bound_);
	}
	vector_delete(self->argument_list, il_factor_call_op_argument_delete);
	MEM_FREE(self);
}

il_factor_call_op* il_factor_cast_call_T_op(il_factor* fact) {
	assert(fact->type == ilfactor_call_op_T);
	return fact->u.call_;
}

//private
static void il_factor_call_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	if(self->type != ilcall_type_undefined_T) {
		return;
	}
	il_factor* receiver = self->receiver;
	//hoge() foo() Namespace::Class() の場合
	if(receiver->type == ilfactor_variable_T) {
		il_factor_invoke_bound_check(self, env);
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->type == ilfactor_member_op_T) {
		il_factor_member_op_check(self, env, cctx);
	//a()() の場合
	} else if(receiver->type == ilfactor_call_op_T) {
		il_factor_subscript_check(self, env, cctx);
	}
	assert(self->type != ilcall_type_undefined_T);
}

static void il_factor_invoke_bound_check(il_factor_call_op* self, enviroment* env) {
	il_factor* receiver = self->receiver;
	il_factor_variable* ilvar = IL_FACT2VAR(receiver);
	il_factor_invoke_bound* bnd = il_factor_invoke_bound_new(ilvar->fqcn->namev);
	assert(ilvar->fqcn->scope_vec->length == 0);
	//入れ替え
	bnd->args = self->argument_list;
	bnd->type_args = ilvar->type_args;
	self->argument_list = NULL;
	ilvar->type_args = NULL;
	self->u.invoke_bound_ = bnd;
	self->type = ilcall_type_invoke_bound_T;
}

static void il_factor_member_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor* receiver = self->receiver;
	il_factor_member_op* ilmem = IL_FACT2MEM(receiver);
	//hoge.foo
	if(ilmem->fact->type == ilfactor_variable_T) {
		il_factor_member_op_check_namebase(self, ilmem, env, cctx);
	} else {
		il_factor_member_op_check_instance(self, ilmem, env, cctx);
	}
}

static void il_factor_member_op_check_namebase(il_factor_call_op* self, il_factor_member_op* ilmem, enviroment* env, call_context* cctx) {
	il_factor_variable* ilvar = IL_FACT2VAR(ilmem->fact);
	//Namespace::Class.foo()
	if(ilvar->fqcn->scope_vec->length > 0) {
		il_factor_member_op_check_static(self, ilmem, ilvar, env, cctx);
	//hoge.foo()
	} else {
		#if defined(DEBUG)
		const char* clname = string_pool_ref2str(ilvar->fqcn->namev);
		#endif
		namespace_* cur = call_context_namespace(cctx);
		class_* ctype = namespace_get_class(cur, ilvar->fqcn->namev);
		if(ctype == NULL) {
			ctype = namespace_get_class(namespace_lang(), ilvar->fqcn->namev);
		}
		if(ctype != NULL) {
			il_factor_member_op_check_static(self, ilmem, ilvar, env, cctx);
		} else {
			il_factor_member_op_check_instance(self, ilmem, env, cctx);
		}
	}
}

static void il_factor_member_op_check_instance(il_factor_call_op* self, il_factor_member_op* ilmem, enviroment* env, call_context* cctx) {
	//入れ替える
	il_factor_invoke* iv = il_factor_invoke_new(ilmem->namev);
	iv->args = self->argument_list;
	iv->receiver = ilmem->fact;
	iv->type_args = ilmem->type_args;
	ilmem->fact = NULL;
	ilmem->type_args = NULL;
	self->type = ilcall_type_invoke_T;
	self->u.invoke_ = iv;
	self->argument_list = NULL;
}

static void il_factor_member_op_check_static(il_factor_call_op* self, il_factor_member_op* ilmem, il_factor_variable* ilvar, enviroment* env, call_context* cctx) {
	il_factor_invoke_static* st = il_factor_invoke_static_new(ilmem->namev);
	self->type = ilcall_type_invoke_static_T;
	self->u.invoke_static_ = st;
	//入れ替える
	st->type_args = ilmem->type_args;
	st->args = self->argument_list;
	st->fqcn = ilvar->fqcn;
	self->argument_list = NULL;
	ilmem->type_args = NULL;
	ilvar->fqcn = NULL;
}

static void il_factor_subscript_check(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor* receiver = self->receiver;
	il_factor_call_op* call_left = IL_FACT2CALL(receiver);
	il_factor_invoke* iv = il_factor_invoke_new(ZERO_VIEW);
	generic_type* receiver_gtype = il_factor_eval(receiver, env, cctx);
	class_* receiver_cl = TYPE2CLASS(GENERIC2TYPE(receiver_gtype));
	int temp;
	iv->u.opov = class_argfind_operator_overload(receiver_cl, operator_sub_script_get_T, self->argument_list, env, cctx, &temp);
	iv->index = temp;
	assert(temp != -1);
	//入れ替える
	iv->args = self->argument_list;
	iv->type_args = vector_new();
	iv->receiver = receiver;
	iv->tag = instance_invoke_subscript_T;
	self->receiver = NULL;
	self->argument_list = NULL;
	self->type = ilcall_type_invoke_T;
	self->u.invoke_ = iv;
}

static void il_factor_call_op_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_call_op_type_argument_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}