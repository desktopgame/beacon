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
static void resolve_non_default(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx);
static void resolve_default(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx);
static void ILInvoke_args_delete(bc_VectorItem item);
static void ILInvoke_check(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx);
static bc_GenericType* ILInvoke_return_gtype(ILInvoke* self);
static void GenerateILInvoke_method(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx);
static void GenerateILInvoke_subscript(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx);

ILInvoke* NewILInvoke(bc_StringView namev) {
	ILInvoke* ret = (ILInvoke*)MEM_MALLOC(sizeof(ILInvoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->tag = INSTANCE_INVOKE_UNDEFINED_T;
	ret->namev = namev;
	ret->resolved = NULL;
	return ret;
}

void GenerateILInvoke(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx) {
	GenerateILInvoke_method(self, env, cctx);
	GenerateILInvoke_subscript(self, env, cctx);
}

void LoadILInvoke(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->index != -1) {
		return;
	}
	bc_CallFrame* cfr = bc_PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Args = self->args;
	cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	cfr->Kind.InstanceInvoke.Receiver = bc_EvalILFactor(self->receiver, env, cctx);
	bc_LoadILFactor(self->receiver, env, cctx);
	ILInvoke_check(self, env, cctx);
	bc_PopCallContext(cctx);
}

bc_GenericType* EvalILInvoke(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx) {
	ILInvoke_check(self, env, cctx);
	if(bc_GetLastPanic()) {
		return NULL;
	}
	bc_GenericType* rgtp = ILInvoke_return_gtype(self);
	bc_GenericType* ret = NULL;
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

char* ILInvokeToString(ILInvoke* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char* invstr = bc_ILFactorToString(self->receiver, env);
	bc_AppendsBuffer(sb, invstr);
	bc_AppendBuffer(sb, '.');
	bc_AppendsBuffer(sb, bc_Ref2Str(self->namev));
	bc_ILTypeArgsToString(sb, self->type_args, env);
	bc_ILArgsToString(sb, self->type_args, env);
	MEM_FREE(invstr);
	return bc_ReleaseBuffer(sb);
}

void DeleteILInvoke(ILInvoke* self) {
	bc_DeleteVector(self->args, ILInvoke_args_delete);
	bc_DeleteVector(self->type_args, bc_VectorDeleterOfNull);
	bc_DeleteILFactor(self->receiver);
	//generic_DeleteType(self->resolved);
	MEM_FREE(self);
}

bc_OperatorOverload* FindSetILInvoke(ILInvoke* self, bc_ILFactor* value, bc_Enviroment* env, bc_CallContext* cctx, int* outIndex) {
	assert(self->tag == INSTANCE_INVOKE_SUBSCRIPT_T);
	bc_Vector* args = bc_NewVector();
	bc_PushVector(args, ((bc_ILArgument*)bc_AtVector(self->args, 0))->Factor);
	bc_PushVector(args, value);
	bc_OperatorOverload* opov = bc_ILFindOperatorOverloadClass(BC_TYPE2CLASS(self->u.opov->Parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	bc_DeleteVector(args, bc_VectorDeleterOfNull);
	return opov;
}
//private
static void resolve_non_default(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	bc_GenericType* receivergType = bc_EvalILFactor(self->receiver, env, cctx);
	bc_GenericType* rgtp = ILInvoke_return_gtype(self);
	if(rgtp->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		//レシーバの実体化された型の中で、
		//メソッドの戻り値 'T' が表す位置に対応する実際の型を取り出す。
		bc_GenericType* instanced_type = (bc_GenericType*)bc_AtVector(receivergType->TypeArgs, rgtp->VirtualTypeIndex);
		self->resolved = bc_CloneGenericType(instanced_type);
		self->resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
	} else if(rgtp->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		bc_GenericType* instanced_type = (bc_GenericType*)bc_AtVector(self->type_args, rgtp->VirtualTypeIndex);
		self->resolved = bc_CloneGenericType(instanced_type);
		self->resolved->Tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(ILInvoke * self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	bc_GenericType* receivergType = bc_EvalILFactor(self->receiver, env, cctx);
	bc_GenericType* rgtp = ILInvoke_return_gtype(self);
//	virtual_type returnvType = self->m->return_vtype;
	//内側に型変数が含まれているかもしれないので、
	//それをここで展開する。
	bc_CallFrame* cfr = bc_PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Receiver = receivergType;
	cfr->Kind.InstanceInvoke.Args = self->args;
	cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	self->resolved = bc_ApplyGenericType(rgtp, cctx);
	bc_PopCallContext(cctx);
}

static void ILInvoke_check(ILInvoke * self, bc_Enviroment * env, bc_CallContext* cctx) {
	//レシーバの読み込み
	bc_LoadILFactor(self->receiver, env, cctx);
	if(bc_GetLastPanic()) {
		return;
	}
	if(self->receiver->Type == ILFACTOR_VARIABLE_T) {
		ILVariable* ilvar = self->receiver->Kind.Variable;
		assert(ilvar->Type != ILVARIABLE_TYPE_STATIC_T);
	}
	//レシーバの型を評価
	bc_GenericType* gtype = bc_EvalILFactor(self->receiver, env, cctx);
	if(bc_GetLastPanic()) {
		return;
	}
	bc_ResolveILTypeArgument(self->type_args, cctx);
	bc_Type* ctype = gtype->CoreType;
	#if defined(DEBUG)
	const char* cname = bc_Ref2Str(bc_GetTypeName(ctype));
	#endif
	//ジェネリックな変数に対しても
	//Objectクラスのメソッドは呼び出せる
	if(ctype == NULL) {
		ctype = BC_TYPE_OBJECT;
	}
	//メソッドを検索
	assert(ctype != NULL);
	int temp = -1;
	self->tag = INSTANCE_INVOKE_METHOD_T;
	self->u.m = bc_ILFindMethodType(ctype, self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp != -1) {
		return;
	}
	//メソッドが見つからなかったら
	//subscript(添字アクセス)として解決する
	if(self->args->Length != 1) {
		//hoge(1) = 0;
		//の形式なら引数は一つのはず
		bc_Panic(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(ctype)),
			bc_Ref2Str(self->namev)
		);
		return;
	}
	self->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
	self->u.opov = bc_ArgFindOperatorOverloadClass(BC_TYPE2CLASS(ctype), OPERATOR_SUB_SCRIPT_GET_T, self->args, env, cctx, &temp);
	self->index = temp;
	if(temp == -1) {
		bc_Panic(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
			bc_Ref2Str(bc_GetTypeName(ctype)),
			bc_Ref2Str(self->namev)
		);
		return;
	}
}

static void ILInvoke_args_delete(bc_VectorItem item) {
	bc_ILArgument* e = (bc_ILArgument*)item;
	bc_DeleteILArgument(e);
}

static bc_GenericType* ILInvoke_return_gtype(ILInvoke* self) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	return self->tag == INSTANCE_INVOKE_METHOD_T ? self->u.m->ReturnGType : self->u.opov->ReturnGType;
}

static void GenerateILInvoke_method(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_METHOD_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		bc_ILTypeArgument* e = (bc_ILTypeArgument*)bc_AtVector(self->type_args, i);
		assert(e->GType != NULL);
		bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		bc_GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->args, i);
		bc_GenerateILFactor(e->Factor, env, cctx);
	}
	bc_GenerateILFactor(self->receiver, env, cctx);
	if(self->u.m->Parent->Tag == TYPE_INTERFACE_T) {
		bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKEINTERFACE);
		bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->u.m->Parent->AbsoluteIndex);
		bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->index);
	} else {
		assert(!bc_IsStaticModifier(self->u.m->Modifier));
		if(self->u.m->Access == ACCESS_PRIVATE_T) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKESPECIAL);
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->index);
		} else {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKEVIRTUAL);
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->index);
		}
	}
}

static void GenerateILInvoke_subscript(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx) {
	assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
	if(self->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		return;
	}
	for(int i=0; i<self->type_args->Length; i++) {
		bc_ILTypeArgument* e = (bc_ILTypeArgument*)bc_AtVector(self->type_args, i);
		assert(e->GType != NULL);
		bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		bc_GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->args, i);
		bc_GenerateILFactor(e->Factor, env, cctx);
	}
	bc_GenerateILFactor(self->receiver, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	bc_AddOpcodeBuf(env->Bytecode, self->index);
}