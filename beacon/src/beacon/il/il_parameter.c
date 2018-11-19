#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/fqcn_cache.h"

ILParameter * NewILParameter(StringView namev) {
	ILParameter* ret = (ILParameter*)MEM_MALLOC(sizeof(ILParameter));
	ret->Name = namev;
	ret->Type = IL_PARAM_TYPE_DEFAULT;
	ret->GCache = bc_NewGenericCache();
	return ret;
}

void DeleteILParameter(ILParameter * self) {
	if (self == NULL) {
		return;
	}
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
