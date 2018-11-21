#include "il_factor_instanceof_impl.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/import_manager.h"
#include "../../env/class_loader.h"
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILFactor* WrapILInstanceOf(ILInstanceOf* self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_INSTANCEOF_T);
	ret->Kind.InstanceOf = self;
	return ret;
}

ILInstanceOf* NewILInstanceOf() {
	ILInstanceOf* ret = (ILInstanceOf*)MEM_MALLOC(sizeof(ILInstanceOf));
	ret->Source = NULL;
	ret->GCache = bc_NewGenericCache();
	return ret;
}

void LoadILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Source, env, cctx);
}

void GenerateILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gtype = bc_ResolveImportManager(NULL, self->GCache, cctx);
	bc_Type* type = gtype->CoreType;
	bc_GenerateILFactor(self->Source, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
	bc_GenerateGenericType(gtype, env);
	bc_AddOpcodeBuf(env->Bytecode, OP_INSTANCEOF);
}

bc_GenericType* EvalILInstanceOf(ILInstanceOf* self, bc_Enviroment* env, bc_CallContext* cctx) {
	return BC_TYPE_BOOL->GenericSelf;
}

char* ILInstanceOfToString(ILInstanceOf* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char* a = bc_ILFactorToString(self->Source, env);
	char* b = bc_GenericCacheToString(self->GCache);
	bc_AppendsBuffer(sb, a);
	bc_AppendsBuffer(sb, " is ");
	bc_AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return bc_ReleaseBuffer(sb);
}

void DeleteILInstanceOf(ILInstanceOf* self) {
	bc_DeleteILFactor(self->Source);
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}