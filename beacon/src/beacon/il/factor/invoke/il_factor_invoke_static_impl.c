#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"
#include "../../../util/vector.h"

//proto
static void resolve_non_default(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx);
static void resolve_default(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx);
static void ILFactor_invoke_static_check(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx);
static void ILFactor_invoke_static_args_delete(VectorItem item);
static void ILFactor_invoke_static_typeargs_delete(VectorItem item);

ILFactor_invoke_static* NewILInvokeStatic(StringView namev) {
	ILFactor_invoke_static* ret = (ILFactor_invoke_static*)MEM_MALLOC(sizeof(ILFactor_invoke_static));
	ret->args = NULL;
	ret->fqcn = NULL;
	ret->type_args = NULL;
	ret->namev = namev;
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void GenerateILInvokeStatic(ILFactor_invoke_static* self, Enviroment* env, CallContext* cctx) {
	for(int i=0; i<self->type_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->type_args, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* e = (ILArgument*)AtVector(self->args, i);
		GenerateILFactor(e->Factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKESTATIC);
	AddOpcodeBuf(env->Bytecode, (VectorItem)self->m->Parent->absolute_index);
	AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
}

void LoadILInvokeStatic(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx) {
	ILFactor_invoke_static_check(self, env, cctx);
}

GenericType* EvalILInvokeStatic(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx) {
	ILFactor_invoke_static_check(self, env, cctx);
	//メソッドを解決できなかった場合
	if(GetLastBCError()) {
		return NULL;
	}
	GenericType* rgtp = self->m->ReturnGType;
	if(rgtp->Tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		return self->resolved;
	}
	return NULL;
}

char* ILInvokeStaticToString(ILFactor_invoke_static* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* name = FQCNCacheToString(self->fqcn);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	ILTypeArgsToString(sb, self->type_args, env);
	ILArgsToString(sb, self->args, env);
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILInvokeStatic(ILFactor_invoke_static* self) {
	DeleteVector(self->args, ILFactor_invoke_static_args_delete);
	DeleteVector(self->type_args, ILFactor_invoke_static_typeargs_delete);
	DeleteFQCNCache(self->fqcn);
	MEM_FREE(self);
}
//private
//FIXME:ILFactor_invokeからのコピペ
static void resolve_non_default(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	GenericType* rgtp = self->m->ReturnGType;
	GenericType* instanced_type = (GenericType*)AtVector(self->type_args, rgtp->VirtualTypeIndex);
	self->resolved = generic_NewType(instanced_type->CoreType);
	self->resolved->Tag = GENERIC_TYPE_TAG_METHOD_T;
	self->resolved->VirtualTypeIndex = rgtp->VirtualTypeIndex;
}

static void resolve_default(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_STATIC_INVOKE_T);
	cfr->Kind.StaticInvoke.Args = self->args;
	cfr->Kind.StaticInvoke.TypeArgs = self->type_args;
	GenericType* rgtp = self->m->ReturnGType;
	self->resolved = ApplyGenericType(rgtp, cctx);
	PopCallContext(cctx);
}

static void ILFactor_invoke_static_check(ILFactor_invoke_static * self, Enviroment* env, CallContext* cctx) {
	type* ty =GetEvalTypeCContext(cctx, self->fqcn);
	if(ty == NULL) {
		ThrowBCError(BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
			Ref2Str(self->fqcn->Name),
			Ref2Str(self->namev)
		);
		return;
	}
	class_* cls = TYPE2CLASS(ty);
	#if defined(DEBUG)
	const char* classname = Ref2Str(cls->namev);
	const char* methodname = Ref2Str(self->namev);
	#endif
	int temp = -1;
	ResolveILTypeArgument(self->type_args, cctx);
	//環境を設定
	//メソッドを検索
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* ilarg = AtVector(self->args, i);
		LoadILFactor(ilarg->Factor, env, cctx);
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_STATIC_INVOKE_T);
	cfr->Kind.StaticInvoke.Args = self->args;
	cfr->Kind.StaticInvoke.TypeArgs = self->type_args;
	self->m = ILFindSMethodClass(cls, self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	//メソッドが見つからない
	if(temp == -1 || self->m == NULL) {
		ThrowBCError(BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,
			Ref2Str(cls->namev),
			Ref2Str(self->namev)
		);
	}
	PopCallContext(cctx);
}

static void ILFactor_invoke_static_args_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static void ILFactor_invoke_static_typeargs_delete(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}