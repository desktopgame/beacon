#include "property_body.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"

property_body* property_body_malloc(property_body_tag tag, const char* filename, int lineno) {
	property_body* ret = mem_malloc(sizeof(property_body), filename, lineno);
	ret->tag = tag;
	ret->env = enviroment_new();
	return ret;
}

void property_body_delete(property_body* self) {
	MEM_FREE(self);
}