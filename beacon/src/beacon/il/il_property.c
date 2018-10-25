#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

ILProperty* MallocILProperty(StringView namev, const char* filename, int lineno) {
	ILProperty* ret = mem_malloc(sizeof(ILProperty), filename, lineno);
	ret->Name = namev;
	ret->GCache = NewGenericCache();
	ret->Set = NULL;
	ret->Get = NULL;
	return ret;
}

void DeleteILProperty(ILProperty* self) {
	DeleteGenericCache(self->GCache);
	DeleteILPropertyBody(self->Set);
	DeleteILPropertyBody(self->Get);
	MEM_FREE(self);
}