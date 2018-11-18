#include "type_cache.h"
#include "../util/mem.h"
#include "cll/class_loader_bcload_impl.h"
#include "class_loader.h"

TypeCache * NewTypeCache() {
	TypeCache* ret = (TypeCache*)MEM_MALLOC(sizeof(TypeCache));
	ret->Context = NULL;
	ret->ILType = NULL;
	ret->Type = NULL;
	ret->Scope = NULL;
	ret->IsConsume = false;
	return ret;
}

TypeCache * InitTypeCache(TypeCache * self, bc_ClassLoader * context, ILType * iltype, Type* tp, Namespace * scope, TypeCacheKind kind) {
	self->Context = context;
	self->ILType = iltype;
	self->Type = tp;
	self->Scope = scope;
	self->Kind = kind;
	return self;
}

void DeleteTypeCache(TypeCache * self) {
	MEM_FREE(self);
}
