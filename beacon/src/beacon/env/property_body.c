#include "property_body.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"

PropertyBody* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno) {
	PropertyBody* ret = mem_malloc(sizeof(PropertyBody), filename, lineno);
	ret->Tag = tag;
	ret->Env = NewEnviroment();
	ret->Parent = NULL;
	return ret;
}

void DeletePropertyBody(PropertyBody* self) {
	DeleteEnviroment(self->Env);
	MEM_FREE(self);
}