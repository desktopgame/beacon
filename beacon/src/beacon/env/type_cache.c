#include "type_cache.h"
#include "../util/mem.h"
#include "cll/class_loader_bcload_impl.h"
#include "class_loader.h"

type_cache * NewTypeCache() {
	type_cache* ret = (type_cache*)MEM_MALLOC(sizeof(type_cache));
	ret->context = NULL;
	ret->iltype = NULL;
	ret->tp = NULL;
	ret->scope = NULL;
	ret->consume = false;
	return ret;
}

type_cache * InitTypeCache(type_cache * self, class_loader * context, il_type * iltype, type * tp, namespace_ * scope, cache_kind kind) {
	self->context = context;
	self->iltype = iltype;
	self->tp = tp;
	self->scope = scope;
	self->kind = kind;
	return self;
}

void DeleteTypeCache(type_cache * self) {
	MEM_FREE(self);
}
