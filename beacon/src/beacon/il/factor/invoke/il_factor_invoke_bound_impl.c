#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../env/operator_overload.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/symbol_entry.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void DeleteILInvokeBound_typeargs(VectorItem item);
static void resolve_non_default(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx);
static void resolve_default(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx);
static void il_factor_invoke_bound_args_delete(VectorItem item);
static void GenerateILInvokeBound_method(il_factor_invoke_bound* self, Enviroment* env, CallContext* cctx);
static void GenerateILInvokeBound_subscript(il_factor_invoke_bound* self, Enviroment* env, CallContext* cctx);
static GenericType* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, CallContext* cctx);
static GenericType* EvalILInvokeBoundImpl(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx);

il_factor_invoke_bound* NewILInvokeBound(StringView namev) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->namev = namev;
	ret->args = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	ret->tag = BOUND_INVOKE_UNDEFINED_T;
	return ret;
}

void GenerateILInvokeBound(il_factor_invoke_bound* self, Enviroment* env, CallContext* cctx) {
	GenerateILInvokeBound_method(self, env, cctx);
	GenerateILInvokeBound_subscript(self, env, cctx);
}

void LoadILInvokeBound(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	il_factor_invoke_bound_check(self, env, cctx);
}

GenericType* EvalILInvokeBound(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	GenericType* ret = EvalILInvokeBoundImpl(self, env, cctx);
	assert(ret != NULL);
	return ret;
}

char* ILInvokeBoundToString(il_factor_invoke_bound* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendsBuffer(sb, Ref2Str(self->namev));
	ILTypeArgsToString(sb, self->type_args, env);
	ILArgsToString(sb, self->type_args, env);
	return ReleaseBuffer(sb);
}

void DeleteILInvokeBound(il_factor_invoke_bound* self) {
	DeleteVector(self->args, il_factor_invoke_bound_args_delete);
	DeleteVector(self->type_args, DeleteILInvokeBound_typeargs);
	//generic_DeleteType(self->resolved);
	MEM_FREE(self);
}

OperatorOverload* FindSetILInvokeBound(il_factor_invoke_bound* self, il_factor* value, Enviroment* env, CallContext* cctx, int* outIndex) {
	assert(self->tag == BOUND_INVOKE_SUBSCRIPT_T);
	Vector* args = NewVector();
	PushVector(args, ((ILArgument*)AtVector(self->args, 0))->Factor);
	PushVector(args, value);
	OperatorOverload* opov = ILFindOperatorOverloadClass(TYPE2CLASS(self->u.subscript.opov->Parent), OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
	DeleteVector(args, VectorDeleterOfNull);
	return opov;
}

//private
//FIXME:il_factor_invokeからのコピペ
static void DeleteILInvokeBound_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}

static void resolve_non_default(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = NULL;
	GenericType* rgtp  = il_factor_invoke_bound_return_gtype(self, cctx);
	if(rgtp->tag == GENERIC_TYPE_TAG_CLASS_T) {
		self->resolved = generic_NewType(NULL);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
		self->resolved->virtual_type_index = rgtp->virtual_type_index;
	} else if(rgtp->tag == GENERIC_TYPE_TAG_METHOD_T) {
		//メソッドに渡された型引数を参照する
		GenericType* instanced_type = (GenericType*)AtVector(self->type_args, rgtp->virtual_type_index);
		self->resolved = generic_NewType(instanced_type->CoreType);
		self->resolved->tag = GENERIC_TYPE_TAG_CLASS_T;
	}
}

static void resolve_default(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	if(self->resolved != NULL) {
		return;
	}
	GenericType* rgtp = il_factor_invoke_bound_return_gtype(self, cctx);
	self->resolved = ApplyGenericType(rgtp, cctx);
}

static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	if(self->index != -1) {
		return;
	}
	//対応するメソッドを検索
	type* ctype = GetTypeCContext(cctx);
	int temp = -1;
	ResolveILTypeArgument(self->type_args, cctx);
	for(int i=0; i<self->args->Length; i++) {
		ILArgument* ilarg = AtVector(self->args, i);
		LoadILFactor(ilarg->Factor, env, cctx);
	}
	BC_ERROR();
	#if defined(DEBUG)
	const char* nstr = Ref2Str(self->namev);
	const char* str = Ref2Str(GetTypeName(ctype));
	#endif
	CallFrame* cfr = PushCallContext(cctx, FRAME_SELF_INVOKE_T);
	cfr->Kind.SelfInvoke.Args = self->args;
	cfr->Kind.SelfInvoke.TypeArgs = self->type_args;
	self->tag = BOUND_INVOKE_METHOD_T;
	self->u.m = ILFindMethodClass(TYPE2CLASS(ctype), self->namev, self->args, env, cctx, &temp);
	self->index = temp;
	BC_ERROR();
	if(self->index != -1) {
		PopCallContext(cctx);
		return;
	}
	//添字アクセスとして解決する
	GenericType* receiver_gtype = NULL;
	SymbolEntry* local = EntrySymbolTable(env->Symboles, NULL, self->namev);
	if(receiver_gtype == NULL && local != NULL) {
		receiver_gtype = local->GType;
		self->u.subscript.tag = SUBSCRIPT_LOCAL_T;
		self->u.subscript.u.local = local;
		self->u.subscript.index = local->Index;
	}
	//フィールドとして解決する
	Field* fi = FindFieldClass(GetClassCContext(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && fi != NULL) {
		receiver_gtype = fi->gtype;
		self->u.subscript.tag = SUBSCRIPT_FIELD_T;
		self->u.subscript.u.fi = fi;
		self->u.subscript.index = temp;
	}
	//プロパティとして解決する
	Property* prop = FindPropertyClass(GetClassCContext(cctx), self->namev, &temp);
	if(receiver_gtype == NULL && prop != NULL) {
		receiver_gtype = prop->GType;
		self->u.subscript.tag = SUBSCRIPT_PROPERTY_T;
		self->u.subscript.u.prop = prop;
		self->u.subscript.index = temp;
	}
	if(receiver_gtype != NULL) {
		self->tag = BOUND_INVOKE_SUBSCRIPT_T;
		self->u.subscript.opov = ArgFindOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), OPERATOR_SUB_SCRIPT_GET_T, self->args, env, cctx, &temp);
		self->index = temp;
		if(temp == -1) {
			ThrowBCError(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
				Ref2Str(self->namev)
			);
		}
	}
	if(self->index == -1) {
		ThrowBCError(BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
			Ref2Str(GetTypeName(ctype)),
			Ref2Str(self->namev)
		);
	}
	PopCallContext(cctx);
}

static void il_factor_invoke_bound_args_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}

static void GenerateILInvokeBound_method(il_factor_invoke_bound* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->tag != BOUND_INVOKE_METHOD_T) {
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
		if(GetLastBCError()) {
			return;
		}
	}
	if(IsStaticModifier(self->u.m->Modifier)) {
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKESTATIC);
		AddOpcodeBuf(env->Bytecode, (VectorItem)self->u.m->Parent->absolute_index);
		AddOpcodeBuf(env->Bytecode,(VectorItem) self->index);
	} else {
		AddOpcodeBuf(env->Bytecode,(VectorItem) OP_THIS);
		if(self->u.m->Access == ACCESS_PRIVATE_T) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKESPECIAL);
			AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
		} else {
			AddOpcodeBuf(env->Bytecode, (VectorItem)OP_INVOKEVIRTUAL);
			AddOpcodeBuf(env->Bytecode, (VectorItem)self->index);
		}
	}
}

static void GenerateILInvokeBound_subscript(il_factor_invoke_bound* self, Enviroment* env, CallContext* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	if(self->tag != BOUND_INVOKE_SUBSCRIPT_T) {
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
		if(GetLastBCError()) {
			return;
		}
	}
	subscript_descriptor subs = self->u.subscript;
	if(subs.tag == SUBSCRIPT_LOCAL_T) {
		AddOpcodeBuf(env->Bytecode, OP_LOAD);
		AddOpcodeBuf(env->Bytecode, subs.index);
	} else if(subs.tag == SUBSCRIPT_FIELD_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetField(env->Bytecode, subs.u.fi, subs.index);
	} else if(subs.tag == SUBSCRIPT_PROPERTY_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetProperty(env->Bytecode, subs.u.prop, subs.index);
	} else {
		assert(false);
	}
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->index);
}

static GenericType* il_factor_invoke_bound_return_gtype(il_factor_invoke_bound* self, CallContext* cctx) {
	assert(self->tag != BOUND_INVOKE_UNDEFINED_T);
	return ApplyGenericType(self->tag == BOUND_INVOKE_METHOD_T ?
			self->u.m->ReturnGType :
			self->u.subscript.opov->ReturnGType, cctx);
}

static GenericType* EvalILInvokeBoundImpl(il_factor_invoke_bound * self, Enviroment * env, CallContext* cctx) {
	type* tp = NULL;
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	CallFrame* cfr = NULL;
	if(self->tag == BOUND_INVOKE_METHOD_T) {
		cfr = PushCallContext(cctx, FRAME_SELF_INVOKE_T);
		cfr->Kind.SelfInvoke.Args = self->args;
		cfr->Kind.SelfInvoke.TypeArgs = self->type_args;
	} else {
		cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
		cfr->Kind.InstanceInvoke.Receiver = ApplyGenericType(subscript_descriptor_receiver(&self->u.subscript), cctx);
		cfr->Kind.InstanceInvoke.Args = self->args;
		cfr->Kind.InstanceInvoke.TypeArgs = self->type_args;
	}

	if(il_factor_invoke_bound_return_gtype(self, cctx)->tag != GENERIC_TYPE_TAG_NONE_T) {
		resolve_non_default(self, env, cctx);
		assert(self->resolved != NULL);
		PopCallContext(cctx);
		return self->resolved;
	} else {
		resolve_default(self, env, cctx);
		assert(self->resolved != NULL);
		PopCallContext(cctx);
		return self->resolved;
	}
	PopCallContext(cctx);
	assert(self->resolved != NULL);
	return self->resolved;
}