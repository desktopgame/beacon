#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "il_factor_interface.h"
#include "../env/generic_cache.h"

il_field * il_field_new(string_view namev) {
	il_field* ret = (il_field*)MEM_MALLOC(sizeof(il_field));
	ret->fqcn = generic_cache_new();
	ret->access = access_public_T;
	ret->modifier = modifier_none_T;
	ret->namev = namev;
	ret->initial_value = NULL;
	return ret;
}

void il_field_dump(il_field * self, int depth) {
	io_printi(depth);
	access_print(self->access);
	printf(" ");
	modifier_print(self->modifier);
	printf(" field ");
	generic_cache_print(self->fqcn);
	printf(" %s", string_pool_ref2str(self->namev));
	io_println();
}

void il_field_delete(il_field * self) {
	if (self == NULL) {
		return;
	}
	il_factor_delete(self->initial_value);
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}
