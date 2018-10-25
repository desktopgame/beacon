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
static void resolve_non_default(il_factor_invoke * self, Enviroment* env, CallContext* cctx);
static void resolve_default(il_factor_invoke * self, Enviroment* env, CallContext* cctx);
static void il_factor_invoke_args_delete(VectorItem item);
static void il_factor_invoke_check(il_factor_invoke * self, Enviroment* env, CallContext* cctx);
static generic_type* il_factor_invoke_return_gtype(il_factor_invoke* self);
static void GenerateILInvoke_method(il_factor_invoke* self, Enviroment* env, CallContext* cctx);
static void GenerateILInvoke_subscript(il_factor_invoke* self, Enviroment* env, CallContext* cctx);

il_factor_invoke* NewILInvoke(StringView namev) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->tag = INSTANCE_INVOKE_UNDEFINED_T;
	ret->namev = namev;
	ret->resolved = NULL;
	return ret;
}

void GenerateILInvoke(il_factor_invoke* self, Enviroment* env, CallContext* cctx) {
	GenerateILInvoke_method(self, env, cctx);
	GenerateILInvoke_subscript(self, env, cctx);
}

void LoadILInvoke(il_factor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->index != -1) {
		return;
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Args = self->args;
	cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	cfr->Kind.InstanceInvoke.Receiver = EvalILFactor(self->receiver, env, cctx);
	LoadILFactor(self->receiver, env, cctx);
	il_factor_invoke_check(self, env, cctx);
	PopCallContext(cctx);
}

generic_type* EvalILInvoke(il_factor_invoke * self, Enviroment* env, CallContext* cctx) {
	il_factor_invoke_check(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
	generic_type* ret = NULL;
	//型変数をそのまま返す場合
	if(rgtp->tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		ret = self->resolved;
	//型変数ではない型を返す
	} else {
		resolve_default(self, env, cctx);
		ret = self->resolved;
	}
	return ret;
}

char* ILInvokeToString(il_factor_invoke* self, Enviroment* env) {
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

void DeleteILInvoke(il_factor_invoke* self) {
	DeleteVector(self->args, il_factor_invoke_args_delete);
	DeleteVector(self->type_args, VectorDeleterOfNull);
	DeleteILFactor(self->receiver);
	//generic_DeleteType(self->resolved);
	MEM_FREE(self);
}

operator_overload* FindSetILInvoke(il_factor_invoke* self, il_factor* value, Enviroment* env, CallContext* cctx, int* outIndex) {
	assert(self->tag == INSTANCE_INVOKE_SUBSCRIPT_T);
	Vector* args = NewVector();
	PushVector(args, ((ILArgument*)AtVector(self->args, 0))->Factor);
	PushVector(args, value);
	operator_overload* opov = ILFindOperatorOverloadClass(TYPE2CLASS(self->u.opov->parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	DeleteVector(args, VectorDeleterOfNull);
	return opov;
}
//private
static void resolve_non_default(il_factor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = EvalILFactor(self->receiver, env, cctx);
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
	if(rgtp->tag == GENERIC_TYPE_TAG_CLASS_T) {
		//レシーバの実体化された型の中で、
		//メソッドの戻り値 'T' が表す位置に対応する実際の型を取り出す。
		generic_type* instanced_type = (generic_type*)AtVector(receivergType->type_args_list, rgtp->virtual_type_index);
		self->resolved = CloneGenericType(instanced_type);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	} else if(rgtp->tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)AtVector(self->type_args, rgtp->virtual_type_index);
		self->resolved = CloneGenericType(instanced_type);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(il_factor_invoke * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	generic_type* receivergType = EvalILFactor(self->receiver, env, cctx);
	generic_type* rgtp = il_factor_invoke_return_gtype(self);
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

static void il_factor_invoke_check(il_factor_invoke * self, Enviroment * env, CallContext* cctx) {
	//レシーバの読み込み
	LoadILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	if(self->receiver->type == ILFACTOR_VARIABLE_T) {
		il_factor_variable* ilvar = self->receiver->u.variable_;
		assert(ilvar->type != ILVARIABLE_TYPE_STATIC_T);
	}
	//レシーバの型を評価
	generic_type* gtype = EvalILFactor(self->receiver, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	ResolveILTypeArgument(self->type_args, cctx);
	type* ctype = gtype->core_type;
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

static void il_factor_invoke_args_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static generic_type* il_factor_invoke_return_gtype(il_factor_invoke* self) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	return self->tag == INSTANCE_INVOKE_METHOD_T ? self->u.m->ReturnGType : self->u.opov->return_gtype;
}

static void GenerateILInvoke_method(il_factor_invoke* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_METHOD_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->gtype, env);
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

static void GenerateILInvoke_subscript(il_factor_invoke* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(self->type_args, i);
		assert(e->gtype != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->gtype, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* e = (ILArgument*)AtVector(self->args, i);
		GenerateILFactor(e->Factor, env, cctx);
	}
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}