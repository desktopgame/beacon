#include "il_factor_instanceof_impl.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/import_manager.h"
#include "../../env/class_loader.h"
#include "../../util/mem.h"
#include "../../util/text.h"

ILFactor* WrapILInstanceOf(ILInstanceOf* self) {
	ILFactor* ret = NewILFactor(ILFACTOR_INSTANCEOF_T);
	ret->Kind.InstanceOf = self;
	return ret;
}

ILInstanceOf* NewILInstanceOf() {
	ILInstanceOf* ret = (ILInstanceOf*)MEM_MALLOC(sizeof(ILInstanceOf));
	ret->Source = NULL;
	ret->GCache = bc_NewGenericCache();
	return ret;
}

void LoadILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Source, env, cctx);
}

void GenerateILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, CallContext* cctx) {
	bc_GenericType* gtype = bc_ResolveImportManager(NULL, self->GCache, cctx);
	bc_Type* type = gtype->CoreType;
	GenerateILFactor(self->Source, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
	bc_GenerateGenericType(gtype, env);
	bc_AddOpcodeBuf(env->Bytecode, OP_INSTANCEOF);
}

bc_GenericType* EvalILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, CallContext* cctx) {
	return BC_TYPE_BOOL->GenericSelf;
}

char* ILInstanceOfToString(ILInstanceOf* self, bc_Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->Source, env);
	char* b = bc_GenericCacheToString(self->GCache);
	AppendsBuffer(sb, a);
	AppendsBuffer(sb, " is ");
	AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return ReleaseBuffer(sb);
}

void DeleteILInstanceOf(ILInstanceOf* self) {
	DeleteILFactor(self->Source);
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}