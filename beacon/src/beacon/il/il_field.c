#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"

il_field * il_field_new(string_view namev) {
	il_field* ret = (il_field*)MEM_MALLOC(sizeof(il_field));
	ret->fqcn = generic_cache_new();
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->namev = namev;
	return ret;
}

void il_field_dump(il_field * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	text_printf(" ");
	modifier_print(self->modifier);
	text_printf(" field ");
	generic_cache_print(self->fqcn);
	text_printf(" %s", string_pool_ref2str(self->namev));
	text_putline();
}

void il_field_delete(il_field * self) {
	if (self == NULL) {
		return;
	}
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}
