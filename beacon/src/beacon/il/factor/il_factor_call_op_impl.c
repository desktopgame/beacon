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
static void ILCallOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx);
static void ILMemberOp_check_namebase(ILCallOp* self, ILMemberOp* ilmem, Enviroment* env, CallContext* cctx);
static void ILMemberOp_check_instance(ILCallOp* self, ILMemberOp* ilmem, Enviroment* env, CallContext* cctx);
static void ILMemberOp_check_static(ILCallOp* self, ILMemberOp* ilmem, ILFactor_variable* ilvar, Enviroment* env, CallContext* cctx);
static void ILFactor_invoke_bound_check(ILCallOp* self, Enviroment* env);
static void ILMemberOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx);
static void ILFactor_subscript_check(ILCallOp* self, Enviroment* env, CallContext* cctx);

static void ILCallOp_argument_delete(VectorItem item);
static void ILCallOp_type_argument_delete(VectorItem item);

ILFactor* WrapCallOp(ILCallOp* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_CALL_OP_T);
	ret->u.call_ = self;
	self->Parent = ret;
	return ret;
}

ILCallOp* NewILCallOp() {
	ILCallOp* ret = (ILCallOp*)MEM_MALLOC(sizeof(ILCallOp));
	ret->Receiver = NULL;
	ret->Arguments = NewVector();
	ret->Type = ILCALL_TYPE_UNDEFINED_T;
	return ret;
}

void LoadCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	//argumentlistはサブクラスに渡しちゃってる
	//LoadILFactor(self->Receiver, env, ilctx, eh);
	ILCallOp_check(self, env, cctx);
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		LoadILInvoke(self->Kind.Invoke, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		LoadILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		LoadILInvokeBound(self->Kind.InvokeBound, env, cctx);
	}
}

GenericType* EvalILCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILCallOp_check(self, env, cctx);
	GenericType* ret = NULL;
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		ret = EvalILInvoke(self->Kind.Invoke, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ret =  EvalILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		ret = EvalILInvokeBound(self->Kind.InvokeBound, env, cctx);
	}
	if(GetLastBCError()) {
		return ret;
	}
	return ret;
}

char* ILCallOpToString(ILCallOp* self, Enviroment* env) {
//	LoadCallOp(self, env);
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		return ILInvokeToString(self->Kind.Invoke, env);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return ILInvokeBoundToString(self->Kind.InvokeBound, env);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return ILInvokeStaticToString(self->Kind.InvokeStatic, env);
	}
	return NULL;
}

void GenerateILCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	LoadCallOp(self, env, cctx);
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		return GenerateILInvoke(self->Kind.Invoke, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		return GenerateILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		return GenerateILInvokeBound(self->Kind.InvokeBound, env, cctx);
	}
}

void DeleteILCallOp(ILCallOp* self) {
	DeleteILFactor(self->Receiver);
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		DeleteILInvoke(self->Kind.Invoke);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		DeleteILInvokeStatic(self->Kind.InvokeStatic);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		DeleteILInvokeBound(self->Kind.InvokeBound);
	}
	DeleteVector(self->Arguments, ILCallOp_argument_delete);
	MEM_FREE(self);
}

//private
static void ILCallOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	if(self->Type != ILCALL_TYPE_UNDEFINED_T) {
		return;
	}
	ILFactor* receiver = self->Receiver;
	//hoge() foo() Namespace::Class() の場合
	if(receiver->type == ILFACTOR_VARIABLE_T) {
		ILFactor_invoke_bound_check(self, env);
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->type == ILFACTOR_MEMBER_OP_T) {
		ILMemberOp_check(self, env, cctx);
	//a()() の場合
	} else if(receiver->type == ILFACTOR_CALL_OP_T) {
		ILFactor_subscript_check(self, env, cctx);
	}
	assert(self->Type != ILCALL_TYPE_UNDEFINED_T);
}

static void ILFactor_invoke_bound_check(ILCallOp* self, Enviroment* env) {
	ILFactor* receiver = self->Receiver;
	ILFactor_variable* ilvar = receiver->u.variable_;
	ILFactor_invoke_bound* bnd = NewILInvokeBound(ilvar->fqcn->Name);
	assert(ilvar->fqcn->Scope->Length == 0);
	//入れ替え
	bnd->args = self->Arguments;
	bnd->type_args = ilvar->type_args;
	self->Arguments = NULL;
	ilvar->type_args = NULL;
	self->Kind.InvokeBound = bnd;
	self->Type = ILCALL_TYPE_INVOKE_BOUND_T;
}

static void ILMemberOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->Receiver;
	ILMemberOp* ilmem = receiver->u.member_;
	//hoge.foo
	if(ilmem->Source->type == ILFACTOR_VARIABLE_T) {
		ILMemberOp_check_namebase(self, ilmem, env, cctx);
	} else {
		ILMemberOp_check_instance(self, ilmem, env, cctx);
	}
}

static void ILMemberOp_check_namebase(ILCallOp* self, ILMemberOp* ilmem, Enviroment* env, CallContext* cctx) {
	ILFactor_variable* ilvar = ilmem->Source->u.variable_;
	//Namespace::Class.foo()
	if(ilvar->fqcn->Scope->Length > 0) {
		ILMemberOp_check_static(self, ilmem, ilvar, env, cctx);
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
			ILMemberOp_check_static(self, ilmem, ilvar, env, cctx);
		} else {
			ILMemberOp_check_instance(self, ilmem, env, cctx);
		}
	}
}

static void ILMemberOp_check_instance(ILCallOp* self, ILMemberOp* ilmem, Enviroment* env, CallContext* cctx) {
	//入れ替える
	ILFactor_invoke* iv = NewILInvoke(ilmem->Name);
	iv->args = self->Arguments;
	iv->receiver = ilmem->Source;
	iv->type_args = ilmem->TypeArgs;
	ilmem->Source = NULL;
	ilmem->TypeArgs = NULL;
	self->Type = ILCALL_TYPE_INVOKE_T;
	self->Kind.Invoke = iv;
	self->Arguments = NULL;
}

static void ILMemberOp_check_static(ILCallOp* self, ILMemberOp* ilmem, ILFactor_variable* ilvar, Enviroment* env, CallContext* cctx) {
	ILFactor_invoke_static* st = NewILInvokeStatic(ilmem->Name);
	self->Type = ILCALL_TYPE_INVOKE_STATIC_T;
	self->Kind.InvokeStatic = st;
	//入れ替える
	st->type_args = ilmem->TypeArgs;
	st->args = self->Arguments;
	st->fqcn = ilvar->fqcn;
	self->Arguments = NULL;
	ilmem->TypeArgs = NULL;
	ilvar->fqcn = NULL;
}

static void ILFactor_subscript_check(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->Receiver;
	ILCallOp* call_left = receiver->u.call_;
	ILFactor_invoke* iv = NewILInvoke(ZERO_VIEW);
	GenericType* receiver_gtype = EvalILFactor(receiver, env, cctx);
	class_* receiver_cl = TYPE2CLASS(GENERIC2TYPE(receiver_gtype));
	int temp;
	iv->u.opov = ArgFindOperatorOverloadClass(receiver_cl, OPERATOR_SUB_SCRIPT_GET_T, self->Arguments, env, cctx, &temp);
	iv->index = temp;
	assert(temp != -1);
	//入れ替える
	iv->args = self->Arguments;
	iv->type_args = NewVector();
	iv->receiver = receiver;
	iv->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
	self->Receiver = NULL;
	self->Arguments = NULL;
	self->Type = ILCALL_TYPE_INVOKE_T;
	self->Kind.Invoke = iv;
}

static void ILCallOp_argument_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static void ILCallOp_type_argument_delete(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}