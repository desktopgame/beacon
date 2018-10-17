#include "property.h"
#include "../util/mem.h"

property* MallocProperty(StringView namev, const char* filename, int lineno) {
	property* ret = mem_malloc(sizeof(property), filename, lineno);
	ret->namev = namev;
	ret->gtype = NULL;
	ret->parent = NULL;
	ret->set = property_body_new(PROPERTY_SET_T);
	ret->get = property_body_new(PROPERTY_GET_T);
	ret->is_short = false;
	ret->source_ref = NULL;
	ret->set->parent = ret;
	ret->get->parent = ret;
	return ret;
}
void DeleteProperty(property* self) {
	DeletePropertyBody(self->set);
	DeletePropertyBody(self->get);
	MEM_FREE(self);
}
