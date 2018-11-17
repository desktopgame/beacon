#include "property.h"
#include "../util/mem.h"

Property* MallocProperty(StringView namev, const char* filename, int lineno) {
	Property* ret = bc_MXMalloc(sizeof(Property), filename, lineno);
	ret->Name = namev;
	ret->GType = NULL;
	ret->Parent = NULL;
	ret->Set = NewPropertyBody(PROPERTY_SET_T);
	ret->Get = NewPropertyBody(PROPERTY_GET_T);
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
