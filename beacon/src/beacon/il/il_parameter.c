#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/fqcn_cache.h"

ILParameter * NewILParameter(StringView namev) {
	ILParameter* ret = (ILParameter*)MEM_MALLOC(sizeof(ILParameter));
	ret->namev = namev;
	ret->param_type = IL_PARAM_TYPE_DEFAULT;
	ret->fqcn = NewGenericCache();
	return ret;
}

void DeleteILParameter(ILParameter * self) {
	if (self == NULL) {
		return;
	}
	DeleteGenericCache(self->fqcn);
	MEM_FREE(self);
}
