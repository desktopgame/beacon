#include "property.h"
#include "../util/mem.h"

Property* MallocProperty(StringView namev, const char* filename, int lineno) {
	Property* ret = mem_malloc(sizeof(Property), filename, lineno);
	ret->Name = namev;
	ret->GType = NULL;
	ret->Parent = NULL;
	ret->Set = PropertyBody_new(PROPERTY_SET_T);
	ret->Get = PropertyBody_new(PROPERTY_GET_T);
	ret->IsShort = false;
	ret->SourceRef = NULL;
	ret->Set->Parent = ret;
	ret->Get->Parent = ret;
	return ret;
}
void DeleteProperty(Property* self) {
	DeletePropertyBody(self->Set);
	DeletePropertyBody(self->Get);
	MEM_FREE(self);
}
