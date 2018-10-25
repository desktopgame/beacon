#include "property_body.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"

property_body* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno) {
	property_body* ret = mem_malloc(sizeof(property_body), filename, lineno);
	ret->tag = tag;
	ret->env = NewEnviroment();
	ret->parent = NULL;
	return ret;
}

void DeletePropertyBody(property_body* self) {
	DeleteEnviroment(self->env);
	MEM_FREE(self);
}