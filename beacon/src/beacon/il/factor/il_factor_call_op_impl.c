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
static void ILMemberOp_check_static(ILCallOp* self, ILMemberOp* ilmem, ILVariable* ilvar, Enviroment* env, CallContext* cctx);
static void ILInvokeBound_check(ILCallOp* self, Enviroment* env);
static void ILMemberOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx);
static void ILSubscript_check(ILCallOp* self, Enviroment* env, CallContext* cctx);

static void ILCallOp_argument_delete(VectorItem item);
static void ILCallOp_type_argument_delete(VectorItem item);

ILFactor* WrapCallOp(ILCallOp* self) {
	ILFactor* ret = NewILFactor(ILFACTOR_CALL_OP_T);
	ret->Kind.Call = self;
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

bc_GenericType* EvalILCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILCallOp_check(self, env, cctx);
	bc_GenericType* ret = NULL;
	if(self->Type == ILCALL_TYPE_INVOKE_T) {
		ret = EvalILInvoke(self->Kind.Invoke, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ret =  EvalILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
	} else if(self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
		ret = EvalILInvokeBound(self->Kind.InvokeBound, env, cctx);
	}
	if(bc_GetLastPanic()) {
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
	if(receiver->Type == ILFACTOR_VARIABLE_T) {
		ILInvokeBound_check(self, env);
	//hoge().hoge() Namespace::Class.foo() の場合
	} else if(receiver->Type == ILFACTOR_MEMBER_OP_T) {
		ILMemberOp_check(self, env, cctx);
	//a()() の場合
	} else if(receiver->Type == ILFACTOR_CALL_OP_T) {
		ILSubscript_check(self, env, cctx);
	}
	assert(self->Type != ILCALL_TYPE_UNDEFINED_T);
}

static void ILInvokeBound_check(ILCallOp* self, Enviroment* env) {
	ILFactor* receiver = self->Receiver;
	ILVariable* ilvar = receiver->Kind.Variable;
	ILInvokeBound* bnd = NewILInvokeBound(ilvar->FQCN->Name);
	assert(ilvar->FQCN->Scope->Length == 0);
	//入れ替え
	bnd->Arguments = self->Arguments;
	bnd->TypeArgs = ilvar->TypeArgs;
	self->Arguments = NULL;
	ilvar->TypeArgs = NULL;
	self->Kind.InvokeBound = bnd;
	self->Type = ILCALL_TYPE_INVOKE_BOUND_T;
}

static void ILMemberOp_check(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->Receiver;
	ILMemberOp* ilmem = receiver->Kind.MemberOp;
	//hoge.foo
	if(ilmem->Source->Type == ILFACTOR_VARIABLE_T) {
		ILMemberOp_check_namebase(self, ilmem, env, cctx);
	} else {
		ILMemberOp_check_instance(self, ilmem, env, cctx);
	}
}

static void ILMemberOp_check_namebase(ILCallOp* self, ILMemberOp* ilmem, Enviroment* env, CallContext* cctx) {
	ILVariable* ilvar = ilmem->Source->Kind.Variable;
	//Namespace::Class.foo()
	if(ilvar->FQCN->Scope->Length > 0) {
		ILMemberOp_check_static(self, ilmem, ilvar, env, cctx);
	//hoge.foo()
	} else {
		#if defined(DEBUG)
		const char* clname = Ref2Str(ilvar->FQCN->Name);
		#endif
		bc_Namespace* cur = GetNamespaceCContext(cctx);
		Class* ctype = bc_FindClassFromNamespace(cur, ilvar->FQCN->Name);
		if(ctype == NULL) {
			ctype = bc_FindClassFromNamespace(bc_GetLangNamespace(), ilvar->FQCN->Name);
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
	ILInvoke* iv = NewILInvoke(ilmem->Name);
	iv->args = self->Arguments;
	iv->receiver = ilmem->Source;
	iv->type_args = ilmem->TypeArgs;
	ilmem->Source = NULL;
	ilmem->TypeArgs = NULL;
	self->Type = ILCALL_TYPE_INVOKE_T;
	self->Kind.Invoke = iv;
	self->Arguments = NULL;
}

static void ILMemberOp_check_static(ILCallOp* self, ILMemberOp* ilmem, ILVariable* ilvar, Enviroment* env, CallContext* cctx) {
	ILInvokeStatic* st = NewILInvokeStatic(ilmem->Name);
	self->Type = ILCALL_TYPE_INVOKE_STATIC_T;
	self->Kind.InvokeStatic = st;
	//入れ替える
	st->TypeArgs = ilmem->TypeArgs;
	st->Arguments = self->Arguments;
	st->FQCN = ilvar->FQCN;
	self->Arguments = NULL;
	ilmem->TypeArgs = NULL;
	ilvar->FQCN = NULL;
}

static void ILSubscript_check(ILCallOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor* receiver = self->Receiver;
	ILCallOp* call_left = receiver->Kind.Call;
	ILInvoke* iv = NewILInvoke(ZERO_VIEW);
	bc_GenericType* receiver_gtype = EvalILFactor(receiver, env, cctx);
	Class* receiver_cl = BC_TYPE2CLASS(bc_GENERIC2TYPE(receiver_gtype));
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