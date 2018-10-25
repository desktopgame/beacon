#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

ILProperty* MallocILProperty(StringView namev, const char* filename, int lineno) {
	ILProperty* ret = mem_malloc(sizeof(ILProperty), filename, lineno);
	ret->namev = namev;
	ret->fqcn = NewGenericCache();
	ret->set = NULL;
	ret->get = NULL;
	return ret;
}

void DeleteILProperty(ILProperty* self) {
	DeleteGenericCache(self->fqcn);
	DeleteILPropertyBody(self->set);
	DeleteILPropertyBody(self->get);
	MEM_FREE(self);
}