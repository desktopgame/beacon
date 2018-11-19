#include "property.h"
#include "../util/mem.h"

bc_Property* bc_MallocProperty(StringView namev, const char* filename, int lineno) {
	bc_Property* ret = bc_MXMalloc(sizeof(bc_Property), filename, lineno);
	ret->Name = namev;
	ret->GType = NULL;
	ret->Parent = NULL;
	ret->Set = bc_NewPropertyBody(PROPERTY_SET_T);
	ret->Get = bc_NewPropertyBody(PROPERTY_GET_T);
	ret->IsShort = false;
	ret->SourceRef = NULL;
	ret->Set->Parent = ret;
	ret->Get->Parent = ret;
	return ret;
}
void bc_DeleteProperty(bc_Property* self) {
	bc_DeletePropertyBody(self->Set);
	bc_DeletePropertyBody(self->Get);
	MEM_FREE(self);
}
