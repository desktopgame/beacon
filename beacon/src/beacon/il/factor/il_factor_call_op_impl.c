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

static void il_factor_call_op_argument_delete(VectorItem item);
static void il_factor_call_op_type_argument_delete(VectorItem item);

il_factor* il_factor_wrap_call_op(il_factor_call_op* self) {
	il_factor* ret = il_factor_new(ILFACTOR_CALL_OP_T);
	ret->u.call_ = self;
	self->parent = ret;
	return ret;
}

il_factor_call_op* il_factor_call_op_new() {
	il_factor_call_op* ret = (il_factor_call_op*)MEM_MALLOC(sizeof(il_factor_call_op));
	ret->receiver = NULL;
	ret->argument_list = NewVector();
	ret->type = ILCALL_TYPE_UNDEFINED_T;
	return ret;
}

void il_factor_call_OP_LOAD(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	//argumentlistはサブクラスに渡しちゃってる
	//il_factor_load(self->receiver, env, ilctx, eh);
	il_factor_call_op_check(self, env, cctx);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		il_factor_invoke_load(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		il_factor_invoke_static_load(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		il_factor_invoke_bound_load(self->u.invoke_bound_, env, cctx);
	}
}

generic_type* il_factor_call_op_eval(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor_call_op_check(self, env, cctx);
	generic_type* ret = NULL;
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		ret = il_factor_invoke_eval(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ret =  il_factor_invoke_static_eval(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		ret = il_factor_invoke_bound_eval(self->u.invoke_bound_, env, cctx);
	}
	if(GetLastBCError()) {
		return ret;
	}
	return ret;
}

char* il_factor_call_op_to_str(il_factor_call_op* self, enviroment* env) {
//	il_factor_call_OP_LOAD(self, env);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		return il_factor_invoke_tostr(self->u.invoke_, env);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return il_factor_invoke_bound_tostr(self->u.invoke_bound_, env);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return il_factor_invoke_static_tostr(self->u.invoke_static_, env);
	}
	return NULL;
}

void il_factor_call_op_generate(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor_call_OP_LOAD(self, env, cctx);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		return il_factor_invoke_generate(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return il_factor_invoke_static_generate(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return il_factor_invoke_bound_generate(self->u.invoke_bound_, env, cctx);
	}
}

void il_factor_call_op_delete(il_factor_call_op* self) {
	il_factor_delete(self->receiver);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		il_factor_invoke_delete(self->u.invoke_);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		il_factor_invoke_static_delete(self->u.invoke_static_);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		il_factor_invoke_bound_delete(self->u.invoke_bound_);
	}
	DeleteVector(self->argument_list, il_factor_call_op_argument_delete);
	MEM_FREE(self);
}

//private
static void il_factor_call_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	if(self->type != ILCALL_TYPE_UNDEFINED_T) {
		return;
	}
	il_factor* receiver = self->receiver;
	//hoge() foo() Namespace::Class() の場合
	if(receiver->type == ILFACTOR_VARIABLE_T) {
		il_factor_invoke_bound_check(self, env);
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->type == ILFACTOR_MEMBER_OP_T) {
		il_factor_member_op_check(self, env, cctx);
	//a()() の場合
	} else if(receiver->type == ILFACTOR_CALL_OP_T) {
		il_factor_subscript_check(self, env, cctx);
	}
	assert(self->type != ILCALL_TYPE_UNDEFINED_T);
}

static void il_factor_invoke_bound_check(il_factor_call_op* self, enviroment* env) {
	il_factor* receiver = self->receiver;
	il_factor_variable* ilvar = receiver->u.variable_;
	il_factor_invoke_bound* bnd = il_factor_invoke_bound_new(ilvar->fqcn->namev);
	assert(ilvar->fqcn->scope_vec->length == 0);
	//入れ替え
	bnd->args = self->argument_list;
	bnd->type_args = ilvar->type_args;
	self->argument_list = NULL;
	ilvar->type_args = NULL;
	self->u.invoke_bound_ = bnd;
	self->type = ILCALL_TYPE_INVOKE_BOUND_T;
}

static void il_factor_member_op_check(il_factor_call_op* self, enviroment* env, call_context* cctx) {
	il_factor* receiver = self->receiver;
	il_factor_member_op* ilmem = receiver->u.member_;
	//hoge.foo
	if(ilmem->fact->type == ILFACTOR_VARIABLE_T) {
		il_factor_member_op_check_namebase(self, ilmem, env, cctx);
	} else {
		il_factor_member_op_check_instance(self, ilmem, env, cctx);
	}
}

static void il_factor_member_op_check_namebase(il_factor_call_op* self, il_factor_member_op* ilmem, enviroment* env, call_context* cctx) {
	il_factor_variable* ilvar = ilmem->fact->u.variable_;
	//Namespace::Class.foo()
	if(ilvar->fqcn->scope_vec->length > 0) {
		il_factor_member_op_check_static(self, ilmem, ilvar, env, cctx);
	//hoge.foo()
	} else {
		#if defined(DEBUG)
		const char* clname = Ref2Str(ilvar->fqcn->namev);
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
	self->type = ILCALL_TYPE_INVOKE_T;
	self->u.invoke_ = iv;
	self->argument_list = NULL;
}

static void il_factor_member_op_check_static(il_factor_call_op* self, il_factor_member_op* ilmem, il_factor_variable* ilvar, enviroment* env, call_context* cctx) {
	il_factor_invoke_static* st = il_factor_invoke_static_new(ilmem->namev);
	self->type = ILCALL_TYPE_INVOKE_STATIC_T;
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
	il_factor_call_op* call_left = receiver->u.call_;
	il_factor_invoke* iv = il_factor_invoke_new(ZERO_VIEW);
	generic_type* receiver_gtype = il_factor_eval(receiver, env, cctx);
	class_* receiver_cl = TYPE2CLASS(GENERIC2TYPE(receiver_gtype));
	int temp;
	iv->u.opov = class_argfind_operator_overload(receiver_cl, OPERATOR_SUB_SCRIPT_GET_T, self->argument_list, env, cctx, &temp);
	iv->index = temp;
	assert(temp != -1);
	//入れ替える
	iv->args = self->argument_list;
	iv->type_args = NewVector();
	iv->receiver = receiver;
	iv->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
	self->receiver = NULL;
	self->argument_list = NULL;
	self->type = ILCALL_TYPE_INVOKE_T;
	self->u.invoke_ = iv;
}

static void il_factor_call_op_argument_delete(VectorItem item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_call_op_type_argument_delete(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}