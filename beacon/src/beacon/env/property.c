#include "property.h"
#include "../util/mem.h"

property* MallocProperty(StringView namev, const char* filename, int lineno) {
	property* ret = mem_malloc(sizeof(property), filename, lineno);
	ret->namev = namev;
	ret->gtype = NULL;
	ret->parent = NULL;
	ret->set = PropertyBody_new(PROPERTY_SET_T);
	ret->get = PropertyBody_new(PROPERTY_GET_T);
	ret->is_short = false;
	ret->source_ref = NULL;
	ret->set->Parent = ret;
	ret->get->Parent = ret;
	return ret;
}
void DeleteProperty(property* self) {
	DeletePropertyBody(self->set);
	DeletePropertyBody(self->get);
	MEM_FREE(self);
}
