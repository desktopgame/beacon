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
	ret->GCache = NewGenericCache();
	ret->GType = NULL;
	ret->Mode = CAST_UNKNOWN_T;
	return ret;
}

void GenerateILAs(ILAs * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->Source, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
	GenerateGenericType(self->GType, env);
	if(self->Mode == CAST_DOWN_T) {
		AddOpcodeBuf(env->Bytecode, OP_DOWN_AS);
	} else {
		AddOpcodeBuf(env->Bytecode, OP_UP_AS);
	}
}

void LoadILAs(ILAs * self, Enviroment * env, CallContext* cctx) {
	if(self->GType != NULL) {
		return;
	}
	LoadILFactor(self->Source, env, cctx);
	self->GType = ResolveImportManager(GetNamespaceCContext(cctx), self->GCache, cctx);
	GenericType* a = EvalILFactor(self->Source, env, cctx);
	//キャスト元がインターフェイスなら常にアップキャスト
	if(self->GType->CoreType != NULL && GENERIC2TYPE(self->GType)->Tag == TYPE_INTERFACE_T) {
		self->Mode = CAST_UP_T;
		return;
	}
	//キャスト先がインターフェイスなら常にアップキャスト
	if(a->CoreType != NULL && GENERIC2TYPE(a)->Tag == TYPE_INTERFACE_T) {
		self->Mode = CAST_DOWN_T;
		return;
	}
	//キャスト先がオブジェクトなら常にアップキャスト
	if(self->GType->CoreType != NULL && self->GType->CoreType == TYPE_OBJECT) {
		self->Mode = CAST_UP_T;
		return;
	}
	int downTo = DistanceGenericType(self->GType, a, cctx);
	int upTo = DistanceGenericType(a, self->GType, cctx);
	//ダウンキャスト
	if(downTo >= 0) {
		self->Mode = CAST_UP_T;
	//アップキャスト
	} else if(upTo >= 0) {
		self->Mode = CAST_DOWN_T;
	//それ以外
	} else {
		bc_Panic(BCERROR_CAST_NOT_COMPATIBLE_T,
			Ref2Str(GetTypeName(a->CoreType)),
			Ref2Str(GetTypeName(self->GType->CoreType))
		);
	}
}

GenericType* EvalILAs(ILAs * self, Enviroment * env, CallContext* cctx) {
	LoadILAs(self, env, cctx);
	return self->GType;
}

void DeleteILAs(ILAs * self) {
	DeleteGenericCache(self->GCache);
	DeleteILFactor(self->Source);
	MEM_FREE(self);
}

char* ILAsToString(ILAs* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* factstr = ILFactorToString(self->Source, env);
	char* to = GenericCacheToString(self->GCache);
	AppendfBuffer(sb, "%s as %s", factstr, to);
	MEM_FREE(factstr);
	MEM_FREE(to);
	return ReleaseBuffer(sb);
}