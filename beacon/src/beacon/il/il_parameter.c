#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/fqcn_cache.h"

bc_ILParameter * bc_NewILParameter(bc_StringView namev) {
	bc_ILParameter* ret = (bc_ILParameter*)MEM_MALLOC(sizeof(bc_ILParameter));
	ret->Name = namev;
	ret->Type = IL_PARAM_TYPE_DEFAULT;
	ret->GCache = bc_NewGenericCache();
	return ret;
}

void bc_DeleteILParameter(bc_ILParameter * self) {
	if (self == NULL) {
		return;
	}
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
