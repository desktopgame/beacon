#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_factor_interface.h"
#include "../env/generic_cache.h"

bc_ILField * bc_NewILField(bc_StringView name) {
	bc_ILField* ret = (bc_ILField*)MEM_MALLOC(sizeof(bc_ILField));
	ret->GCache = bc_NewGenericCache();
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Name = name;
	ret->InitialValue = NULL;
	return ret;
}

void bc_DeleteILField(bc_ILField * self) {
	if (self == NULL) {
		return;
	}
	bc_DeleteILFactor(self->InitialValue);
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
