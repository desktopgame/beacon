#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_factor_interface.h"
#include "../env/generic_cache.h"

ILField * NewILField(bc_StringView name) {
	ILField* ret = (ILField*)MEM_MALLOC(sizeof(ILField));
	ret->GCache = bc_NewGenericCache();
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Name = name;
	ret->InitialValue = NULL;
	return ret;
}

void DeleteILField(ILField * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->InitialValue);
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
