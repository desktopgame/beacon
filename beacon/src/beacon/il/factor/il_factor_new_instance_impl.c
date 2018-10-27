#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../il_argument.h"
#include "../il_type_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/constructor.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

//proto
static void DeleteILNewInstance_typearg(VectorItem item);
static void ILFactor_new_instance_find(ILFactor_new_instance * self, Enviroment * env, CallContext* cctx);
static void il_Factor_new_instace_delete_arg(VectorItem item);

ILFactor * WrapILNewInstance(ILFactor_new_instance * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_NEW_INSTANCE_T);
	ret->u.new_instance_ = self;
	return ret;
}

ILFactor_new_instance * NewILNewInstance() {
	ILFactor_new_instance* ret = (ILFactor_new_instance*)MEM_MALLOC(sizeof(ILFactor_new_instance));
	ret->fqcnc = FQCNCache_new();
	ret->type_args = NewVector();
	ret->argument_list = NewVector();
	ret->c = NULL;
	ret->constructor_index = -1;
	ret->instance_type = NULL;
	return ret;
}

void GenerateILNewInstance(ILFactor_new_instance * self, Enviroment * env, CallContext* cctx) {
	ILFactor_new_instance_find(self, env, cctx);
	for(int i=0; i<self->type_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->type_args, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		GenerateGenericType(e->GType, env);
	}
	//実引数を全てスタックへ
	for (int i = 0; i < self->argument_list->Length; i++) {
		ILArgument* ilarg = (ILArgument*)AtVector(self->argument_list, i);
		GenerateILFactor(ilarg->Factor, env, cctx);
		if(GetLastBCError()) {
			return;
		}
	}
	//クラスとコンストラクタのインデックスをプッシュ
	AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
	AddOpcodeBuf(env->Bytecode, self->c->Parent->absolute_index);
	AddOpcodeBuf(env->Bytecode, self->constructor_index);
}

void LoadILNewInstance(ILFactor_new_instance * self, Enviroment * env, CallContext* cctx) {
	ILFactor_new_instance_find(self, env, cctx);
	if(GetLastBCError()) {
		return;
	}
	//抽象クラスはインスタンス化できない
	if(IsAbstractType(self->c->Parent)) {
		ThrowBCError(BCERROR_CONSTRUCT_ABSTRACT_TYPE_T, Ref2Str(GetTypeName(self->c->Parent)));
	}
}

GenericType* EvalILNewInstance(ILFactor_new_instance * self, Enviroment * env, CallContext* cctx) {
	ILFactor_new_instance_find(self, env, cctx);
	if(GetLastBCError()) {
		return NULL;
	}
	//型引数がないのでそのまま
	if (self->type_args->Length == 0) {
		GenericType* ret = RefGenericType(self->c->Parent);
		return ret;
	}
	//FQCNCache typename_group
	if (self->instance_type == NULL) {
		Namespace* scope = NULL;
		GenericType* a = generic_NewType(self->c->Parent);
		for (int i = 0; i < self->type_args->Length; i++) {
			ILTypeArgument* e = (ILTypeArgument*)AtVector(self->type_args, i);
			GenericType* arg = ResolveImportManager(GetNamespaceCContext(cctx), e->GCache, cctx);
			AddArgsGenericType(a, arg);
		}
		self->instance_type = a;
	}
	return self->instance_type;
}

char* ILNewInstanceToString(ILFactor_new_instance* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendsBuffer(sb, "new ");
	char* type = FQCNCacheToString(self->fqcnc);
	AppendsBuffer(sb, type);
	ILTypeArgsToString(sb, self->type_args, env);
	ILArgsToString(sb, self->argument_list, env);
	MEM_FREE(type);
	return ReleaseBuffer(sb);
}

void DeleteILNewInstance(ILFactor_new_instance * self) {
	DeleteVector(self->argument_list, il_Factor_new_instace_delete_arg);
	DeleteVector(self->type_args, DeleteILNewInstance_typearg);
	DeleteFQCNCache(self->fqcnc);
	MEM_FREE(self);
}

//private
static void DeleteILNewInstance_typearg(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}

static void ILFactor_new_instance_find(ILFactor_new_instance * self, Enviroment * env, CallContext* cctx) {
	if(self->constructor_index != -1) {
		return;
	}
	#if defined(DEBUG)
	const char* namea = Ref2Str(self->fqcnc->Name);
	if(self->fqcnc->Name == InternString("Vector")) {
		int a = 0;
	}
	#endif
	//コンストラクタで生成するオブジェクトの肩を取得
	type* ty = GetEvalTypeCContext(cctx, self->fqcnc);
	if(ty == NULL) {
		ThrowBCError(BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T,
			Ref2Str(self->fqcnc->Name)
		);
		return;
	}
	//使用するコンストラクタを取得
	class_* cls = TYPE2CLASS(ty);
	int temp = -1;
	CallFrame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
	cfr->Kind.Resolve.GType = cls->parent->generic_self;
	cfr->Kind.Resolve.TypeArgs = self->type_args;
	ResolveILTypeArgument(self->type_args, cctx);
	self->c = ILFindConstructorClass(cls, self->argument_list, env, cctx, &temp);
	self->constructor_index = temp;
	PopCallContext(cctx);
	if(temp == -1) {
		ThrowBCError(BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T,
			Ref2Str(cls->namev)
		);
	}
}

static void il_Factor_new_instace_delete_arg(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}