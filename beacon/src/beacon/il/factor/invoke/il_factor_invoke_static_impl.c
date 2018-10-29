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
static void resolve_non_default(ILInvokeStatic * self, Enviroment* env, CallContext* cctx);
static void resolve_default(ILInvokeStatic * self, Enviroment* env, CallContext* cctx);
static void ILInvokeStatic_check(ILInvokeStatic * self, Enviroment* env, CallContext* cctx);
static void ILInvokeStatic_args_delete(VectorItem item);
static void ILInvokeStatic_typeargs_delete(VectorItem item);

ILInvokeStatic* NewILInvokeStatic(StringView namev) {
	ILInvokeStatic* ret = (ILInvokeStatic*)MEM_MALLOC(sizeof(ILInvokeStatic));
	ret->Arguments = NULL;
	ret->FQCN = NULL;
	ret->TypeArgs = NULL;
	ret->Name = namev;
	ret->Method = NULL;
	ret->Index = -1;
	ret->Resolved = NULL;
	return ret;
}

void GenerateILInvokeStatic(ILInvokeStatic* self, Enviroment* env, CallContext* cctx) {
	for(int i=0; i<self->TypeArgs->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->TypeArgs, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->GType, env);
	}
	for(int i=0; i<self->Arguments->Length; i++) {
		ILArgument* e = (ILArgument*)AtVector(self->Arguments, i);
		GenerateILFactor(e->Factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKESTATIC);
	AddOpcodeBuf(env->Bytecode, (VectorItem)self->Method->Parent->absolute_index);
	AddOpcodeBuf(env->Bytecode, (VectorItem)self->Index);
}

void LoadILInvokeStatic(ILInvokeStatic * self, Enviroment* env, CallContext* cctx) {
	ILInvokeStatic_check(self, env, cctx);
}

GenericType* EvalILInvokeStatic(ILInvokeStatic * self, Enviroment* env, CallContext* cctx) {
	ILInvokeStatic_check(self, env, cctx);
	//メソッドを解決できなかった場合
	if(GetLastBCError()) {
		return NULL;
	}
	GenericType* rgtp = self->Method->ReturnGType;
	if(rgtp->Tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		return self->Resolved;
	} else {
		resolve_default(self, env, cctx);
		return self->Resolved;
	}
	return NULL;
}

char* ILInvokeStaticToString(ILInvokeStatic* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* name = FQCNCacheToString(self->FQCN);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->Name));
	ILTypeArgsToString(sb, self->TypeArgs, env);
	ILArgsToString(sb, self->Arguments, env);
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILInvokeStatic(ILInvokeStatic* self) {
	DeleteVector(self->Arguments, ILInvokeStatic_args_delete);
	DeleteVector(self->TypeArgs, ILInvokeStatic_typeargs_delete);
	DeleteFQCNCache(self->FQCN);
	MEM_FREE(self);
}
//private
//FIXME:ILInvokeからのコピペ
static void resolve_non_default(ILInvokeStatic * self, Enviroment* env, CallContext* cctx) {
	if(self->Resolved != NULL) {
		return;
	}
	GenericType* rgtp = self->Method->ReturnGType;
	GenericType* instanced_type = (GenericType*)AtVector(self->TypeArgs, rgtp->VirtualTypeIndex);
	self->Resolved = generic_NewType(instanced_type->CoreType);
	self->Resolved->Tag = GENERIC_TYPE_TAG_METHOD_T;
	self->Resolved->VirtualTypeIndex = rgtp->VirtualTypeIndex;
}

static void resolve_default(ILInvokeStatic * self, Enviroment* env, CallContext* cctx) {
	if(self->Resolved != NULL) {
		return;
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_STATIC_INVOKE_T);
	cfr->Kind.StaticInvoke.Args = self->Arguments;
	cfr->Kind.StaticInvoke.TypeArgs = self->TypeArgs;
	GenericType* rgtp = self->Method->ReturnGType;
	self->Resolved = ApplyGenericType(rgtp, cctx);
	PopCallContext(cctx);
}

static void ILInvokeStatic_check(ILInvokeStatic * self, Enviroment* env, CallContext* cctx) {
	type* ty =GetEvalTypeCContext(cctx, self->FQCN);
	if(ty == NULL) {
		ThrowBCError(BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
			Ref2Str(self->FQCN->Name),
			Ref2Str(self->Name)
		);
		return;
	}
	class_* cls = TYPE2CLASS(ty);
	#if defined(DEBUG)
	const char* classname = Ref2Str(cls->namev);
	const char* methodname = Ref2Str(self->Name);
	#endif
	int temp = -1;
	ResolveILTypeArgument(self->TypeArgs, cctx);
	//環境を設定
	//メソッドを検索
	for(int i=0; i<self->Arguments->Length; i++) {
		ILArgument* ilarg = AtVector(self->Arguments, i);
		LoadILFactor(ilarg->Factor, env, cctx);
	}
	CallFrame* cfr = PushCallContext(cctx, FRAME_STATIC_INVOKE_T);
	cfr->Kind.StaticInvoke.Args = self->Arguments;
	cfr->Kind.StaticInvoke.TypeArgs = self->TypeArgs;
	self->Method = ILFindSMethodClass(cls, self->Name, self->Arguments, env, cctx, &temp);
	self->Index = temp;
	//メソッドが見つからない
	if(temp == -1 || self->Method == NULL) {
		ThrowBCError(BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,
			Ref2Str(cls->namev),
			Ref2Str(self->Name)
		);
	}
	PopCallContext(cctx);
}

static void ILInvokeStatic_args_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static void ILInvokeStatic_typeargs_delete(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}