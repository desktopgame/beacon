#include "il_property.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"

bc_ILProperty* bc_MallocILProperty(bc_StringView namev, const char* filename, int lineno) {
	bc_ILProperty* ret = bc_MXMalloc(sizeof(bc_ILProperty), filename, lineno);
	ret->Name = namev;
	ret->GCache = bc_NewGenericCache();
	ret->Set = NULL;
	ret->Get = NULL;
	return ret;
}

void bc_DeleteILProperty(bc_ILProperty* self) {
	bc_DeleteGenericCache(self->GCache);
	bc_DeleteILPropertyBody(self->Set);
	bc_DeleteILPropertyBody(self->Get);
	MEM_FREE(self);
}