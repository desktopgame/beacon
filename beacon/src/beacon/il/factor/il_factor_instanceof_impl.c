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
	ILFactor* ret = ILFactor_new(ILFACTOR_INSTANCEOF_T);
	ret->u.instanceof_ = self;
	return ret;
}

ILInstanceOf* NewILInstanceOf() {
	ILInstanceOf* ret = (ILInstanceOf*)MEM_MALLOC(sizeof(ILInstanceOf));
	ret->Source = NULL;
	ret->GCache = NewGenericCache();
	return ret;
}

void LoadILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Source, env, cctx);
}

void GenerateILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx) {
	GenericType* gtype = ResolveImportManager(NULL, self->GCache, cctx);
	Type* type = gtype->CoreType;
	GenerateILFactor(self->Source, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
	GenerateGenericType(gtype, env);
	AddOpcodeBuf(env->Bytecode, OP_INSTANCEOF);
}

GenericType* EvalILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx) {
	return TYPE_BOOL->GenericSelf;
}

char* ILInstanceOfToString(ILInstanceOf* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->Source, env);
	char* b = GenericCacheToString(self->GCache);
	AppendsBuffer(sb, a);
	AppendsBuffer(sb, " is ");
	AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return ReleaseBuffer(sb);
}

void DeleteILInstanceOf(ILInstanceOf* self) {
	DeleteILFactor(self->Source);
	DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}