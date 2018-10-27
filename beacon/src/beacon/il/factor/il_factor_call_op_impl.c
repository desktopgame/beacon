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
static void ILFactor_call_op_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);
static void ILFactor_member_op_check_namebase(ILFactor_call_op* self, ILFactor_member_op* ilmem, Enviroment* env, CallContext* cctx);
static void ILFactor_member_op_check_instance(ILFactor_call_op* self, ILFactor_member_op* ilmem, Enviroment* env, CallContext* cctx);
static void ILFactor_member_op_check_static(ILFactor_call_op* self, ILFactor_member_op* ilmem, ILFactor_variable* ilvar, Enviroment* env, CallContext* cctx);
static void ILFactor_invoke_bound_check(ILFactor_call_op* self, Enviroment* env);
static void ILFactor_member_op_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);
static void ILFactor_subscript_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx);

static void ILFactor_call_op_argument_delete(VectorItem item);
static void ILFactor_call_op_type_argument_delete(VectorItem item);

ILFactor* WrapCallOp(ILFactor_call_op* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_CALL_OP_T);
	ret->u.call_ = self;
	self->parent = ret;
	return ret;
}

ILFactor_call_op* NewILCallOp() {
	ILFactor_call_op* ret = (ILFactor_call_op*)MEM_MALLOC(sizeof(ILFactor_call_op));
	ret->receiver = NULL;
	ret->argument_list = NewVector();
	ret->type = ILCALL_TYPE_UNDEFINED_T;
	return ret;
}

void LoadCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	//argumentlistはサブクラスに渡しちゃってる
	//LoadILFactor(self->receiver, env, ilctx, eh);
	ILFactor_call_op_check(self, env, cctx);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		LoadILInvoke(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		LoadILInvokeStatic(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		LoadILInvokeBound(self->u.invoke_bound_, env, cctx);
	}
}

GenericType* EvalILCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	ILFactor_call_op_check(self, env, cctx);
	GenericType* ret = NULL;
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		ret = EvalILInvoke(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ret =  EvalILInvokeStatic(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		ret = EvalILInvokeBound(self->u.invoke_bound_, env, cctx);
	}
	if(GetLastBCError()) {
		return ret;
	}
	return ret;
}

char* ILCallOpToString(ILFactor_call_op* self, Enviroment* env) {
//	LoadCallOp(self, env);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		return ILInvokeToString(self->u.invoke_, env);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return ILInvokeBoundToString(self->u.invoke_bound_, env);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return ILInvokeStaticToString(self->u.invoke_static_, env);
	}
	return NULL;
}

void GenerateILCallOp(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	LoadCallOp(self, env, cctx);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		return GenerateILInvoke(self->u.invoke_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return GenerateILInvokeStatic(self->u.invoke_static_, env, cctx);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return GenerateILInvokeBound(self->u.invoke_bound_, env, cctx);
	}
}

void DeleteILCallOp(ILFactor_call_op* self) {
	DeleteILFactor(self->receiver);
	if(self->type == ILCALL_TYPE_INVOKE_T) {
		DeleteILInvoke(self->u.invoke_);
	} else if(self->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		DeleteILInvokeStatic(self->u.invoke_static_);
	} else if(self->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		DeleteILInvokeBound(self->u.invoke_bound_);
	}
	DeleteVector(self->argument_list, ILFactor_call_op_argument_delete);
	MEM_FREE(self);
}

//private
static void ILFactor_call_op_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	if(self->type != ILCALL_TYPE_UNDEFINED_T) {
		return;
	}
	ILFactor* receiver = self->receiver;
	//hoge() foo() Namespace::Class() の場合
	if(receiver->type == ILFACTOR_VARIABLE_T) {
		ILFactor_invoke_bound_check(self, env);
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->type == ILFACTOR_MEMBER_OP_T) {
		ILFactor_member_op_check(self, env, cctx);
	//a()() の場合
	} else if(receiver->type == ILFACTOR_CALL_OP_T) {
		ILFactor_subscript_check(self, env, cctx);
	}
	assert(self->type != ILCALL_TYPE_UNDEFINED_T);
}

static void ILFactor_invoke_bound_check(ILFactor_call_op* self, Enviroment* env) {
	ILFactor* receiver = self->receiver;
	ILFactor_variable* ilvar = receiver->u.variable_;
	ILFactor_invoke_bound* bnd = NewILInvokeBound(ilvar->fqcn->Name);
	assert(ilvar->fqcn->Scope->Length == 0);
	//入れ替え
	bnd->args = self->argument_list;
	bnd->type_args = ilvar->type_args;
	self->argument_list = NULL;
	ilvar->type_args = NULL;
	self->u.invoke_bound_ = bnd;
	self->type = ILCALL_TYPE_INVOKE_BOUND_T;
}

static void ILFactor_member_op_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->receiver;
	ILFactor_member_op* ilmem = receiver->u.member_;
	//hoge.foo
	if(ilmem->fact->type == ILFACTOR_VARIABLE_T) {
		ILFactor_member_op_check_namebase(self, ilmem, env, cctx);
	} else {
		ILFactor_member_op_check_instance(self, ilmem, env, cctx);
	}
}

static void ILFactor_member_op_check_namebase(ILFactor_call_op* self, ILFactor_member_op* ilmem, Enviroment* env, CallContext* cctx) {
	ILFactor_variable* ilvar = ilmem->fact->u.variable_;
	//Namespace::Class.foo()
	if(ilvar->fqcn->Scope->Length > 0) {
		ILFactor_member_op_check_static(self, ilmem, ilvar, env, cctx);
	//hoge.foo()
	} else {
		#if defined(DEBUG)
		const char* clname = Ref2Str(ilvar->fqcn->Name);
		#endif
		Namespace* cur = GetNamespaceCContext(cctx);
		class_* ctype = FindClassFromNamespace(cur, ilvar->fqcn->Name);
		if(ctype == NULL) {
			ctype = FindClassFromNamespace(GetLangNamespace(), ilvar->fqcn->Name);
		}
		if(ctype != NULL) {
			ILFactor_member_op_check_static(self, ilmem, ilvar, env, cctx);
		} else {
			ILFactor_member_op_check_instance(self, ilmem, env, cctx);
		}
	}
}

static void ILFactor_member_op_check_instance(ILFactor_call_op* self, ILFactor_member_op* ilmem, Enviroment* env, CallContext* cctx) {
	//入れ替える
	ILFactor_invoke* iv = NewILInvoke(ilmem->namev);
	iv->args = self->argument_list;
	iv->receiver = ilmem->fact;
	iv->type_args = ilmem->type_args;
	ilmem->fact = NULL;
	ilmem->type_args = NULL;
	self->type = ILCALL_TYPE_INVOKE_T;
	self->u.invoke_ = iv;
	self->argument_list = NULL;
}

static void ILFactor_member_op_check_static(ILFactor_call_op* self, ILFactor_member_op* ilmem, ILFactor_variable* ilvar, Enviroment* env, CallContext* cctx) {
	ILFactor_invoke_static* st = NewILInvokeStatic(ilmem->namev);
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

static void ILFactor_subscript_check(ILFactor_call_op* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->receiver;
	ILFactor_call_op* call_left = receiver->u.call_;
	ILFactor_invoke* iv = NewILInvoke(ZERO_VIEW);
	GenericType* receiver_gtype = EvalILFactor(receiver, env, cctx);
	class_* receiver_cl = TYPE2CLASS(GENERIC2TYPE(receiver_gtype));
	int temp;
	iv->u.opov = ArgFindOperatorOverloadClass(receiver_cl, OPERATOR_SUB_SCRIPT_GET_T, self->argument_list, env, cctx, &temp);
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

static void ILFactor_call_op_argument_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static void ILFactor_call_op_type_argument_delete(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}