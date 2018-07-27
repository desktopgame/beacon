#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/fqcn_cache.h"

il_parameter * il_parameter_new(string_view namev) {
	il_parameter* ret = (il_parameter*)MEM_MALLOC(sizeof(il_parameter));
	ret->namev = namev;
	ret->param_type = il_param_type_default;
	ret->fqcn = generic_cache_new();
	return ret;
}

void il_parameter_dump(il_parameter * self, int depth) {
	text_putindent(depth);
	text_printf("parameter %s ", string_pool_ref2str(self->namev));
	generic_cache_print(self->fqcn);
	text_putline();
}

void il_parameter_delete(il_parameter * self) {
	if (self == NULL) {
		return;
	}
	generic_cache_delete(self->fqcn);
	MEM_FREE(self);
}
