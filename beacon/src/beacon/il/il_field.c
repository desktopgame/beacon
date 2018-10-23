#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_factor_interface.h"
#include "../env/generic_cache.h"

ILField * NewILField(StringView namev) {
	ILField* ret = (ILField*)MEM_MALLOC(sizeof(ILField));
	ret->fqcn = NewGenericCache();
	ret->access = ACCESS_PUBLIC_T;
	ret->modifier = MODIFIER_NONE_T;
	ret->namev = namev;
	ret->initial_value = NULL;
	return ret;
}

void DeleteILField(ILField * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->initial_value);
	DeleteGenericCache(self->fqcn);
	MEM_FREE(self);
}
