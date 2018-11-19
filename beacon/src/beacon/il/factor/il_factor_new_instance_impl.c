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
static void ILNewInstance_find(ILNewInstance * self, Enviroment * env, CallContext* cctx);
static void il_Factor_new_instace_delete_arg(VectorItem item);

ILFactor * WrapILNewInstance(ILNewInstance * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_NEW_INSTANCE_T);
	ret->Kind.NewInstance = self;
	return ret;
}

ILNewInstance * NewILNewInstance() {
	ILNewInstance* ret = (ILNewInstance*)MEM_MALLOC(sizeof(ILNewInstance));
	ret->FQCNCache = bc_NewFQCNCache();
	ret->TypeArgs = NewVector();
	ret->Arguments = NewVector();
	ret->Constructor = NULL;
	ret->ConstructorIndex = -1;
	ret->InstanceGType = NULL;
	return ret;
}

void GenerateILNewInstance(ILNewInstance * self, Enviroment * env, CallContext* cctx) {
	ILNewInstance_find(self, env, cctx);
	for(int i=0; i<self->TypeArgs->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(self->TypeArgs, i);
		assert(e->GType != NULL);
		AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
		bc_GenerateGenericType(e->GType, env);
	}
	//実引数を全てスタックへ
	for (int i = 0; i < self->Arguments->Length; i++) {
		ILArgument* ilarg = (ILArgument*)AtVector(self->Arguments, i);
		GenerateILFactor(ilarg->Factor, env, cctx);
		if(bc_GetLastPanic()) {
			return;
		}
	}
	//クラスとコンストラクタのインデックスをプッシュ
	AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
	AddOpcodeBuf(env->Bytecode, self->Constructor->Parent->AbsoluteIndex);
	AddOpcodeBuf(env->Bytecode, self->ConstructorIndex);
}

void LoadILNewInstance(ILNewInstance * self, Enviroment * env, CallContext* cctx) {
	ILNewInstance_find(self, env, cctx);
	if(bc_GetLastPanic()) {
		return;
	}
	//抽象クラスはインスタンス化できない
	if(bc_IsAbstractType(self->Constructor->Parent)) {
		bc_Panic(BCERROR_CONSTRUCT_ABSTRACT_TYPE_T, Ref2Str(bc_GetTypeName(self->Constructor->Parent)));
	}
}

bc_GenericType* EvalILNewInstance(ILNewInstance * self, Enviroment * env, CallContext* cctx) {
	ILNewInstance_find(self, env, cctx);
	if(bc_GetLastPanic()) {
		return NULL;
	}
	//型引数がないのでそのまま
	if (self->TypeArgs->Length == 0) {
		bc_GenericType* ret = bc_RefGenericType(self->Constructor->Parent);
		return ret;
	}
	//FQCNCache typename_group
	if (self->InstanceGType == NULL) {
		bc_Namespace* scope = NULL;
		bc_GenericType* a = bc_NewGenericType(self->Constructor->Parent);
		for (int i = 0; i < self->TypeArgs->Length; i++) {
			ILTypeArgument* e = (ILTypeArgument*)AtVector(self->TypeArgs, i);
			bc_GenericType* arg = bc_ResolveImportManager(GetNamespaceCContext(cctx), e->GCache, cctx);
			bc_AddArgsGenericType(a, arg);
		}
		self->InstanceGType = a;
	}
	return self->InstanceGType;
}

char* ILNewInstanceToString(ILNewInstance* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendsBuffer(sb, "new ");
	char* type = bc_FQCNCacheToString(self->FQCNCache);
	AppendsBuffer(sb, type);
	ILTypeArgsToString(sb, self->TypeArgs, env);
	ILArgsToString(sb, self->Arguments, env);
	MEM_FREE(type);
	return ReleaseBuffer(sb);
}

void DeleteILNewInstance(ILNewInstance * self) {
	DeleteVector(self->Arguments, il_Factor_new_instace_delete_arg);
	DeleteVector(self->TypeArgs, DeleteILNewInstance_typearg);
	bc_DeleteFQCNCache(self->FQCNCache);
	MEM_FREE(self);
}

//private
static void DeleteILNewInstance_typearg(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}

static void ILNewInstance_find(ILNewInstance * self, Enviroment * env, CallContext* cctx) {
	if(self->ConstructorIndex != -1) {
		return;
	}
	#if defined(DEBUG)
	const char* namea = Ref2Str(self->FQCNCache->Name);
	if(self->FQCNCache->Name == InternString("Vector")) {
		int a = 0;
	}
	#endif
	//コンストラクタで生成するオブジェクトの肩を取得
	bc_Type* ty = GetEvalTypeCContext(cctx, self->FQCNCache);
	if(ty == NULL) {
		bc_Panic(BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T,
			Ref2Str(self->FQCNCache->Name)
		);
		return;
	}
	//使用するコンストラクタを取得
	bc_Class* cls = BC_TYPE2CLASS(ty);
	int temp = -1;
	CallFrame* cfr = PushCallContext(cctx, FRAME_RESOLVE_T);
	cfr->Kind.Resolve.GType = cls->Parent->GenericSelf;
	cfr->Kind.Resolve.TypeArgs = self->TypeArgs;
	ResolveILTypeArgument(self->TypeArgs, cctx);
	self->Constructor = bc_ILFindConstructorClass(cls, self->Arguments, env, cctx, &temp);
	self->ConstructorIndex = temp;
	PopCallContext(cctx);
	if(temp == -1) {
		bc_Panic(BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T,
			Ref2Str(cls->Name)
		);
	}
}

static void il_Factor_new_instace_delete_arg(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}