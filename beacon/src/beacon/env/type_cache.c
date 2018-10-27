#include "type_cache.h"
#include "../util/mem.h"
#include "cll/class_loader_bcload_impl.h"
#include "class_loader.h"

TypeCache * NewTypeCache() {
	TypeCache* ret = (TypeCache*)MEM_MALLOC(sizeof(TypeCache));
	ret->context = NULL;
	ret->iltype = NULL;
	ret->tp = NULL;
	ret->scope = NULL;
	ret->consume = false;
	return ret;
}

TypeCache * InitTypeCache(TypeCache * self, ClassLoader * context, il_type * iltype, type * tp, Namespace * scope, TypeCacheKind kind) {
	self->context = context;
	self->iltype = iltype;
	self->tp = tp;
	self->scope = scope;
	self->kind = kind;
	return self;
}

void DeleteTypeCache(TypeCache * self) {
	MEM_FREE(self);
}
