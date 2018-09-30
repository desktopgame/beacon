#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_factor_interface.h"
#include "../env/generic_cache.h"

il_field * NewILField(string_view namev) {
	il_field* ret = (il_field*)MEM_MALLOC(sizeof(il_field));
	ret->fqcn = generic_cache_new();
	ret->access = ACCESS_PUBLIC_T;
	ret->modifier = MODIFIER_NONE_T;
	ret->namev = namev;
	ret->initial_value = NULL;
	return ret;
}

void DeleteILField(il_field * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->initial_value);
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}
