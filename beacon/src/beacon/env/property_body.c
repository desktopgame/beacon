#include "property_body.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"

PropertyBody* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno) {
	PropertyBody* ret = mem_malloc(sizeof(PropertyBody), filename, lineno);
	ret->tag = tag;
	ret->env = NewEnviroment();
	ret->parent = NULL;
	return ret;
}

void DeletePropertyBody(PropertyBody* self) {
	DeleteEnviroment(self->env);
	MEM_FREE(self);
}