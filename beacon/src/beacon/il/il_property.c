#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

il_property* MallocILProperty(string_view namev, const char* filename, int lineno) {
	il_property* ret = mem_malloc(sizeof(il_property), filename, lineno);
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	ret->set = NULL;
	ret->get = NULL;
	return ret;
}

void DeleteILProperty(il_property* self) {
	generic_cache_delete(self->fqcn);
	il_property_body_delete(self->set);
	il_property_body_delete(self->get);
	MEM_FREE(self);
}