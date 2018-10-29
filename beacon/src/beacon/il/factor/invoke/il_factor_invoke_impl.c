#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/method.h"
#include "../../../env/class_loader.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../il_factor_impl.h"
#include <string.h>
#include <stdio.h>

//proto
static void resolve_non_default(ILFactor_invoke * self, Enviroment* env, CallContext* cctx);
static void resolve_default(ILFactor_invoke * self, Enviroment* env, CallContext* cctx);
static void ILFactor_invoke_args_delete(VectorItem item);
static void ILFactor_invoke_check(ILFactor_invoke * self, Enviroment* env, CallContext* cctx);
static GenericType* ILFactor_invoke_return_gtype(ILFactor_invoke* self);
static void GenerateILInvoke_method(ILFactor_invoke* self, Enviroment* env, CallContext* cctx);
static void GenerateILInvoke_subscript(ILFactor_invoke* self, Enviroment* env, CallContext* cctx);

ILFactor_invoke* NewILInvoke(StringView namev) {
	ILFactor_invoke* ret = (ILFactor_invoke*)MEM_MALLOC(sizeof(ILFactor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->tag = INSTANCE_INVOKE_UNDEFINED_T;
	ret->namev = namev;
	ret->resolved = NULL;
	return ret;
}

void GenerateILInvoke(ILFactor_invoke* self, Enviroment* env, CallContext* cctx) {
	GenerateILInvoke_method(self, env, cctx);
	GenerateILInvoke_subscript(self, env, cctx);
}

void LoadILInvoke(ILFactor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->index != -1) {
		return;
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Args = self->args;
	cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	cfr->Kind.InstanceInvoke.Receiver = EvalILFactor(self->receiver, env, cctx);
	LoadILFactor(self->receiver, env, cctx);
	ILFactor_invoke_check(self, env, cctx);
	PopCallContext(cctx);
}

GenericType* EvalILInvoke(ILFactor_invoke * self, Enviroment* env, CallContext* cctx) {
	ILFactor_invoke_check(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	GenericType* rgtp = ILFactor_invoke_return_gtype(self);
	GenericType* ret = NULL;
	//型変数をそのまま返す場合
	if(rgtp->Tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		ret = self->resolved;
	//型変数ではない型を返す
	} else {
		resolve_default(self, env, cctx);
		ret = self->resolved;
	}
	return ret;
}

char* ILInvokeToString(ILFactor_invoke* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* invstr = ILFactorToString(self->receiver, env);
	AppendsBuffer(sb, invstr);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	ILTypeArgsToString(sb, self->type_args, env);
	ILArgsToString(sb, self->type_args, env);
	MEM_FREE(invstr);
	return ReleaseBuffer(sb);
}

void DeleteILInvoke(ILFactor_invoke* self) {
	DeleteVector(self->args, ILFactor_invoke_args_delete);
	DeleteVector(self->type_args, VectorDeleterOfNull);
	DeleteILFactor(self->receiver);
	//generic_DeleteType(self->resolved);
	MEM_FREE(self);
}

OperatorOverload* FindSetILInvoke(ILFactor_invoke* self, ILFactor* value, Enviroment* env, CallContext* cctx, int* outIndex) {
	assert(self->tag == INSTANCE_INVOKE_SUBSCRIPT_T);
	Vector* args = NewVector();
	PushVector(args, ((ILArgument*)AtVector(self->args, 0))->Factor);
	PushVector(args, value);
	OperatorOverload* opov = ILFindOperatorOverloadClass(TYPE2CLASS(self->u.opov->Parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	DeleteVector(args, VectorDeleterOfNull);
	return opov;
}
//private
static void resolve_non_default(ILFactor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	GenericType* receivergType = EvalILFactor(self->receiver, env, cctx);
	GenericType* rgtp = ILFactor_invoke_return_gtype(self);
	if(rgtp->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		//レシーバの実体化された型の中で、
		//メソッドの戻り値 'T' が表す位置に対応する実際の型を取り出す。
		GenericType* instanced_type = (GenericType*)AtVector(receivergType->TypeArgs, rgtp->VirtualTypeIndex);
		self->resolved = CloneGenericType(instanced_type);
		self->resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
	} else if(rgtp->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		GenericType* instanced_type = (GenericType*)AtVector(self->type_args, rgtp->VirtualTypeIndex);
		self->resolved = CloneGenericType(instanced_type);
		self->resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(ILFactor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	GenericType* receivergType = EvalILFactor(self->receiver, env, cctx);
	GenericType* rgtp = ILFactor_invoke_return_gtype(self);
//	virtual_type returnvType = self->m->return_vtype;
	//内側に型変数が含まれているかもしれないので、
	//それをここで展開する。
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Receiver = receivergType;
	cfr->Kind.InstanceInvoke.Args = self->args;
	cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	self->resolved = ApplyGenericType(rgtp, cctx);
	PopCallContext(cctx);
}

static void ILFactor_invoke_check(ILFactor_invoke * self, Enviroment * env, CallContext* cctx) {
	//レシーバの読み込み
	LoadILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	if(self->receiver->type == ILFACTOR_VARIABLE_T) {
		ILFactor_variable* ilvar = self->receiver->u.variable_;
		assert(ilvar->Type != ILVARIABLE_TYPE_STATIC_T);
	}
	//レシーバの型を評価
	GenericType* gtype = EvalILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	ResolveILTypeArgument(self->type_args, cctx);
	type* ctype = gtype->CoreType;
	#if defined(DEBUG)
	const char* cname = Ref2Str(GetTypeName(ctype));
	#endif
	//ジェネリックな変数に対しても
	//Objectクラスのメソッドは呼び出せる
	if(ctype == NULL) {
		ctype = TYPE_OBJECT;
	}
	//メソッドを検索
	assert(ctype != NULL);
	int temp = -1;
	self->tag = INSTANCE_INVOKE_METHOD_T;
	self->u.m = ILFindMethodType(ctype, self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp != -1) {
		return;
	}
	//メソッドが見つからなかったら
	//subscript(添字アクセス)として解決する
	if(self->args->Length != 1) {
		//hoge(1) = 0;
		//の形式なら引数は一つのはず
		ThrowBCError(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			Ref2Str(GetTypeName(ctype)),
			Ref2Str(self->namev)
		);
		return;
	}
	self->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
	self->u.opov = ArgFindOperatorOverloadClass(TYPE2CLASS(ctype), OPERATOR_SUB_SCRIPT_GET_T, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp == -1) {
		ThrowBCError(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			Ref2Str(GetTypeName(ctype)),
			Ref2Str(self->namev)
		);
		return;
	}
}

static void ILFactor_invoke_args_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static GenericType* ILFactor_invoke_return_gtype(ILFactor_invoke* self) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	return self->tag == INSTANCE_INVOKE_METHOD_T ? self->u.m->ReturnGType : self->u.opov->ReturnGType;
}

static void GenerateILInvoke_method(ILFactor_invoke* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_METHOD_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->type_args, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* e = (ILArgument*)AtVector(self->args, i);
		GenerateILFactor(e->Factor, env, cctx);
	}
	GenerateILFactor(self->receiver, env, cctx);
	if(self->u.m->Parent->tag == TYPE_INTERFACE_T) {
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKEINTERFACE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)self->u.m->Parent->absolute_index);
		AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
	} else {
		assert(!IsStaticModifier(self->u.m->Modifier));
		if(self->u.m->Access == ACCESS_PRIVATE_T) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKESPECIAL);
			AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
		} else {
			AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKEVIRTUAL);
			AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
		}
	}
}

static void GenerateILInvoke_subscript(ILFactor_invoke* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->type_args, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* e = (ILArgument*)AtVector(self->args, i);
		GenerateILFactor(e->Factor, env, cctx);
	}
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}