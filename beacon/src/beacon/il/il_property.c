#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

il_property* MallocILProperty(string_view namev, const char* filename, int lineno) {
	il_property* ret = mem_malloc(sizeof(il_property), filename, lineno);
	ret->namev = namev;
	ret->fqcn = NewGenericCache();
	ret->set = NULL;
	ret->get = NULL;
	return ret;
}

void DeleteILProperty(il_property* self) {
	DeleteGenericCache(self->fqcn);
	DeleteILPropertyBody(self->set);
	DeleteILPropertyBody(self->get);
	MEM_FREE(self);
}