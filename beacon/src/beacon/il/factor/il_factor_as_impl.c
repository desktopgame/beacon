#include "il_factor_as_impl.h"
#include "../../util/mem.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <assert.h>

ILFactor * WrapILAs(ILAs * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_AS_T);
	ret->Kind.As = self;
	return ret;
}

ILAs * NewILAs() {
	ILAs* ret = (ILAs*)MEM_MALLOC(sizeof(ILAs));
	ret->Source = NULL;
	ret->GCache = bc_NewGenericCache();
	ret->GType = NULL;
	ret->Mode = CAST_UNKNOWN_T;
	return ret;
}

void GenerateILAs(ILAs * self, bc_Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->Source, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
	bc_GenerateGenericType(self->GType, env);
	if(self->Mode == CAST_DOWN_T) {
		bc_AddOpcodeBuf(env->Bytecode, OP_DOWN_AS);
	} else {
		bc_AddOpcodeBuf(env->Bytecode, OP_UP_AS);
	}
}

void LoadILAs(ILAs * self, bc_Enviroment * env, CallContext* cctx) {
	if(self->GType != NULL) {
		return;
	}
	LoadILFactor(self->Source, env, cctx);
	self->GType = bc_ResolveImportManager(GetNamespaceCContext(cctx), self->GCache, cctx);
	bc_GenericType* a = EvalILFactor(self->Source, env, cctx);
	//キャスト元がインターフェイスなら常にアップキャスト
	if(self->GType->CoreType != NULL && bc_GENERIC2TYPE(self->GType)->Tag == TYPE_INTERFACE_T) {
		self->Mode = CAST_UP_T;
		return;
	}
	//キャスト先がインターフェイスなら常にアップキャスト
	if(a->CoreType != NULL && bc_GENERIC2TYPE(a)->Tag == TYPE_INTERFACE_T) {
		self->Mode = CAST_DOWN_T;
		return;
	}
	//キャスト先がオブジェクトなら常にアップキャスト
	if(self->GType->CoreType != NULL && self->GType->CoreType == BC_TYPE_OBJECT) {
		self->Mode = CAST_UP_T;
		return;
	}
	int downTo = bc_DistanceGenericType(self->GType, a, cctx);
	int upTo = bc_DistanceGenericType(a, self->GType, cctx);
	//ダウンキャスト
	if(downTo >= 0) {
		self->Mode = CAST_UP_T;
	//アップキャスト
	} else if(upTo >= 0) {
		self->Mode = CAST_DOWN_T;
	//それ以外
	} else {
		bc_Panic(BCERROR_CAST_NOT_COMPATIBLE_T,
			Ref2Str(bc_GetTypeName(a->CoreType)),
			Ref2Str(bc_GetTypeName(self->GType->CoreType))
		);
	}
}

bc_GenericType* EvalILAs(ILAs * self, bc_Enviroment * env, CallContext* cctx) {
	LoadILAs(self, env, cctx);
	return self->GType;
}

void DeleteILAs(ILAs * self) {
	bc_DeleteGenericCache(self->GCache);
	DeleteILFactor(self->Source);
	MEM_FREE(self);
}

char* ILAsToString(ILAs* self, bc_Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* factstr = ILFactorToString(self->Source, env);
	char* to = bc_GenericCacheToString(self->GCache);
	AppendfBuffer(sb, "%s as %s", factstr, to);
	MEM_FREE(factstr);
	MEM_FREE(to);
	return ReleaseBuffer(sb);
}